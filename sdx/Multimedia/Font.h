//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>
#include <Multimedia/IFont.h>
#include <Multimedia/SystemFont.h>
#include <Multimedia/Image.h>
#include <Framework/ImagePack.h>
#include <Multimedia/Window.h>
#include <Multimedia/File.h>

#include <map>
#include <unordered_map>
#include <iomanip>

namespace SDX
{
    /** TrueTypeFontとBMPFontをまとめて扱うクラス.*/
    /** 毎回レンダリングせず、ハッシュマップにImageを格納する*/
    /** 一度も表示していない文字が必要になった場合生成し以後使いまわす*/
    /** @todo 高さが違う文字が混ざった場合の仕様が未定、現状上揃え*/
    /** \include Font.h*/
    class Font : public IFont
    {
    private:
        TTF_Font* handle = nullptr;//!<
        bool isBlendRender;
        int size = 0;//!<

        int differenceHeight = 0;//!<
        int enterHeight = 0;//!<
		mutable std::unordered_map<int, Image*> hash;//!<

        int style = TTF_STYLE_NORMAL;//!<
        
        static bool GetUTFSize(unsigned char 一文字目,int &文字長さ )
        {
            if (一文字目 < 0x20)
            {
                //制御文字
                文字長さ = 1;
                return false;
            }

            if (一文字目 < 0x80){ 文字長さ = 1; }
            else if (一文字目 < 0xE0){ 文字長さ = 2; }
            else if (一文字目 < 0xF0){ 文字長さ = 3; }
            else { 文字長さ = 4; }
            return true;
        }

        /** UTFの文字列を一文字ずつ描画.*/
        void DrawUTFString(const Point &座標, const std::string &文字列 , const Color &描画色) const
        {
            Point 位置 = 座標;

            int charSize;
            for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
            {
                if (!GetUTFSize(*it, charSize)){ continue; }
                if (handle == nullptr && *it == ' ')
                {
                    位置.x += size;
                    continue;
                }

                Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str() , charSize);
                if (str == nullptr){ continue; }

                str->SetColor(描画色);
                str->Draw(位置);
                位置.x += str->GetWidth();
            }
        }
        /** UTFの文字列を一文字ずつ拡大描画.*/
        void DrawUTFString(const Point &座標, double X拡大率, double Y拡大率, const std::string &文字列, const Color &描画色) const
        {
            Point 位置 = 座標;

            int charSize = 0;
            for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
            {
                if (!GetUTFSize(*it, charSize)){ continue; }//制御文字は無視
                
                Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(),charSize);
                if (str == nullptr)
                {
                    位置.x += size * X拡大率;
                    continue;
                }

                str->SetColor(描画色);
                str->DrawExtend({ 位置.x , 位置. y ,  str->GetWidth()*X拡大率, str->GetHeight()*Y拡大率 });
                位置.x += str->GetWidth() * X拡大率;
            }
        }
        /** UTFの文字列を一文字ずつ回転拡大描画.*/
        void DrawRotateUTFString(const Point &座標, int X補正, int Y補正, double 拡大率, double 角度, const std::string &文字列, const Color &描画色) const
        {
            Point 位置 = 座標;

            int charSize = 0;
            for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
            {
                if (!GetUTFSize(*it, charSize)){ continue; }

                Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(),charSize);
                if (str == nullptr)
                {
                    位置.x += size * 拡大率;
                    continue;
                }

                X補正 += int(str->GetWidth() * 拡大率 * 0.5);
                double x = 位置.x + std::cos(角度) * X補正 + std::cos(角度 + PAI / 2) * Y補正;
                double y = 位置.y + std::sin(角度) * X補正 + std::sin(角度 + PAI / 2) * Y補正;

                str->SetColor(描画色);
                str->DrawRotate({ x, y }, 拡大率, 角度);
                X補正 += int(str->GetWidth() * 拡大率 * 0.5);
            }
        }

        /** 文字イメージが生成されているか確認し、無ければ新規に生成する.*/
        Image* GetHash(const char* 文字 , int 文字長さ) const
        {
            int ID = 文字[0];
            if (文字長さ >= 2){ ID += 文字[1]*256; }
            if (文字長さ >= 3){ ID += 文字[2]*256*256; }
            if (文字長さ >= 4){ ID += 文字[3] * 256 * 256 * 256; }

            auto it = hash.find(ID);

            if (it == hash.end())
            {
                if (handle == nullptr){ return nullptr; }

                SDL_Surface* surface = nullptr;

#ifndef OMIT_SDL2_TTF
                if (isBlendRender)
                {
                    surface = TTF_RenderUTF8_Blended(handle, 文字, { 255, 255, 255 });
                }
                else
                {
                    surface = TTF_RenderUTF8_Solid(handle, 文字, { 255, 255, 255 });
                }
#endif

                SDL_Texture* moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), surface);				
                hash[ID] = new Image(moji, surface->w, surface->h);

                SDL_FreeSurface(surface);
                return hash[ID];
            }
            return it->second;
        }

        /** 指定した文字に対応する画像を設定.*/
        void SetHash(const char* 文字, int 文字長さ, Image *対応Image)
        {
            int ID = 文字[0];
            if (文字長さ >= 2){ ID += 文字[1] * 256; }
            if (文字長さ >= 3){ ID += 文字[2] * 256 * 256; }
            if (文字長さ >= 4){ ID += 文字[3] * 256 * 256 * 256; }

            hash[ID] = 対応Image;
        }
    public:

        Font() = default;

        /** コンストラクタ*/
        Font(const char *フォント名, int 大きさ, int 行間 = 0 , bool 高品質レンダリングフラグ = true )
        {
            Load(フォント名, 大きさ, 行間, 高品質レンダリングフラグ);
        }

        /** フォントを作成する.*/
        /**	行間は0の場合、改行後の文字が上下くっつく。\n*/
        /** BMPフォント専用にしたい場合、SetSizeを使うと良い*/
        bool Load(const char *フォント名, int 大きさ, int 行間 = 0 , int Y座標差分 = 0, bool 高品質レンダリングフラグ = true )
        {
            if (Loading::isLoading)
            {
                Loading::AddLoading([=]{ Load(フォント名, 大きさ, 行間, 高品質レンダリングフラグ); });
                return true;
            }

            //すでに読み込んでいる場合は失敗
            if (handle != nullptr){ return false; }

            this->size = 大きさ;
            this->enterHeight = 行間 + 大きさ;
            this->differenceHeight = Y座標差分;
            isBlendRender = 高品質レンダリングフラグ;

#ifndef OMIT_SDL2_TTF
            handle = TTF_OpenFont(フォント名, 大きさ);
#endif

            return (handle != nullptr);
        }


        /** フォントハンドルをメモリから開放する.*/
        bool Release() const
        {
            //すでに読み込んでいる場合は失敗
            if (handle != nullptr){ return false; }
            TTF_CloseFont(handle);
            for (auto && it : hash)
            {
                it.second->Release();
            }
            return true;
        }

        /** フォントのハンドルを取得.*/
        TTF_Font* GetHandle() const
        {
            return handle;
        }

        /** FontからImageを生成.*/
        Image MakeImage(Color 文字色, bool 反転フラグ, const VariadicStream &描画する文字列) const
        {
            if (handle == nullptr){ return Image(); }

            int 幅 = GetDrawStringWidth(描画する文字列);
            int 高さ = ((int)描画する文字列.StringS.size() - 1) * enterHeight + size;
            int Y座標 = 0;

            std::vector<SDL_Surface*> surfaces;
            SDL_Surface* surface;

            for (auto it : 描画する文字列.StringS)
            {
                if (isBlendRender)
                {
                    surface = TTF_RenderUTF8_Blended(handle, it.c_str(), 文字色);
                }
                else
                {
                    surface = TTF_RenderUTF8_Solid(handle, it.c_str(), 文字色);
                }

                幅 = std::max(幅, surface->w);
                surfaces.push_back(surface);
            }

            SDL_Surface* toRend = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0, 0, 0, 0);
            SDL_Renderer* render = SDL_CreateSoftwareRenderer(toRend);

            for (auto it : surfaces)
            {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(render, it);

                SDL_Rect temp = { 0, Y座標, it->w, it->h };
                SDL_RenderCopy(render, texture, 0, &temp);

                Y座標 += this->enterHeight;

                SDL_FreeSurface(it);
                SDL_DestroyTexture(texture);
            }
            //描画先を戻す
            Image image(SDL_CreateTextureFromSurface(Screen::GetHandle(), toRend), 幅, 高さ);

            SDL_FreeSurface(toRend);
            SDL_DestroyRenderer(render);

            return image;
        }

		/** フォントの行間を再指定する.*/
		/** Loadしたフォントの大きさが変化するわけでは無い\n*/
		/** BMPフォント専用にしたい場合、Loadでは無くこっちが良い*/
		void SetSize(int 大きさ, int 行間 = 0)
		{
			this->size = 大きさ;
			this->enterHeight = 行間 + 大きさ;
		}

        /** BMPフォントデータを生成する.*/
        /** テキストファイルには出力したい文字を一行で入力します\n*/
        /** pngに変換したい場合、生成したBMPの黒の箇所を透明にして下さい\n*/
        /** 等幅フォントのみ対応*/
        bool MakeBMPFont(const std::string テキストファイル名)
        {
            if (handle == nullptr){ return false; }
            SDL_Surface* surface;
            SDL_Surface* buff;

            SDL_Rect pos;
            SDL_Rect rect;
            rect.x = 0;
            rect.y = 0;
            pos.x = 0;
            pos.y = 0;

            /* OpenGLのテクスチャとして使うために
            各ピクセルがR,G,B,A順の32bitサーフェイスを生成する */
            Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
#else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
#endif
            //追加フォント
            File file(テキストファイル名.c_str(), FileMode::Read, true);
            auto strS = file.GetLineS();
            int count = (int)strS.size();

            unsigned int index = 0;

            if( (unsigned char)strS[0][0] == 0xEF && (unsigned char)strS[0][1] == 0xBB && (unsigned char)strS[0][2] == 0xBF ){index = 3;}

            while(1)
            {
                if( strS[0].size() <= index ){break;}

                if( (unsigned char)strS[0][index] < 0x80 ){index += 1;}
                else if ( (unsigned char)strS[0][index] < 0xE0){ index += 2; }
                else if ( (unsigned char)strS[0][index] < 0xF0){ index += 3; }
                else { index += 4; }

                ++count;
            }

            int high = TTF_FontHeight(handle);
            surface = SDL_CreateRGBSurface(0, size * 32 , high * (12+((count+31)/32) ) , 32, rmask, gmask, bmask, amask);

            std::string str;

            //基本フォントを生成
            for (int a = 0; a < 12; ++a)
            {
                //全角32文字ずつ
                switch (a)
                {
                    case  0: str = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"; break;
                    case  1: str = "abcdefghijklmnopqrstuvwxyz{|}~｡｢｣､･ｦｧｨｩｪｫｬｭｮｯｰｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿ"; break;
                    case  2: str = "ﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜﾝﾞﾟ "; break;
                    case  3: str = "ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただ"; break;
                    case  4: str = "ちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむ"; break;
                    case  5: str = "めもゃやゅゆょよらりるれろゎわゐゑをんゔゕゖ　"; break;
                    case  6: str = "ァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダ"; break;
                    case  7: str = "チヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミム"; break;
                    case  8: str = "メモャヤュユョヨラリルレロヮワヰヱヲンヴヵヶヷヸヹヺ・ーヽヾヿ゠"; break;
                    case  9: str = "！＂＃＄％＆＇（）＊＋，－．／０１２３４５６７８９：；＜＝＞？＠"; break;
                    case 10: str = "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ［＼］＾＿｀"; break;
                    case 11: str = "ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ｛｜｝～｟｠"; break;
                }
                
                if (isBlendRender)
                {
                    buff = TTF_RenderUTF8_Blended(handle, str.c_str(), { 255, 255, 255 });
                }
                else
                {
                    buff = TTF_RenderUTF8_Solid(handle, str.c_str(), { 255, 255, 255 });
                }
                pos.w = buff->w;
                pos.h = buff->h;

                SDL_BlitSurface(buff, NULL, surface, &pos);

                pos.y += high;
                SDL_FreeSurface(buff);
            }


            //一文字ずつ
            //http://1bit.mobi/20101026101350.html 常用漢字表
            index = 0;
            int length = 0;
            //BOMチェック
            if( (unsigned char)strS[0][0] == 0xEF && (unsigned char)strS[0][1] == 0xBB && (unsigned char)strS[0][2] == 0xBF ){index = 3;}

            while(1)
            {
                if( strS[0].size() <= index ){break;}

                if( (unsigned char)strS[0][index] < 0x80 )
                {
                    length = 1;
                }
                else if ( (unsigned char)strS[0][index] < 0xE0)
                {
                    length = 2; 
                }
                else if ( (unsigned char)strS[0][index] < 0xF0)
                {
                    length = 3; 
                }
                else
                {
                    length = 4;
                }
                if (isBlendRender)
                {
                    buff = TTF_RenderUTF8_Blended(handle, strS[0].substr(index,length).c_str() , { 255, 255, 255 });
                }
                else
                {
                    buff = TTF_RenderUTF8_Solid(handle, strS[0].substr(index,length).c_str() , { 255, 255, 255 });
                }

                index += length;

                pos.w = buff->w;
                pos.h = buff->h;

                SDL_BlitSurface(buff, NULL, surface, &pos);

                pos.x += pos.w;
                if (pos.x >= size * 32)
                {
                    pos.x = 0;
                    pos.y += high;
                }
                SDL_FreeSurface(buff);
            }

            std::string fileName = TTF_FontFaceFamilyName(handle);
            fileName += TTF_FontFaceStyleName(handle);
            fileName += std::to_string(size);
            fileName += ".bmp";

            SDL_SaveBMP(surface, fileName.c_str());
            SDL_FreeSurface(surface);

            return true;
        }

        /** MakeBMPFontで生成したBMPフォントデータを読み込む.*/
        /** テキストファイルはMakeBMPFontに使った物と同じ物を使用して下さい*/
        bool LoadBMPFont( const Image& BMPフォント , const std::string テキストファイル名)
        {
            if (Loading::isLoading)
            {
                Loading::AddLoading([=]{ LoadBMPFont(BMPフォント, テキストファイル名); });
                return true;
            }

            File file(テキストファイル名.c_str(), FileMode::Read, true);
            auto strS = file.GetLineS();
            int count = 0;

            unsigned int index = 0;

            if( (unsigned char)strS[0][0] == 0xEF && (unsigned char)strS[0][1] == 0xBB && (unsigned char)strS[0][2] == 0xBF ){index = 3;}

            while(1)
            {
                if( strS[0].size() <= index ){break;}

                if( (unsigned char)strS[0][index] < 0x80 ){index += 1;}
                else if ( (unsigned char)strS[0][index] < 0xE0){ index += 2; }
                else if ( (unsigned char)strS[0][index] < 0xF0){ index += 3; }
                else { index += 4; }

                ++count;
            }

            int h = BMPフォント.GetHeight() / ((count+31)/32 + 12);
            int w = BMPフォント.GetWidth() / 32;

            size = w;
            enterHeight = h;

            std::string str;

            for (int a = 0; a < 12; ++a)
            {
                switch (a)
                {
                    case  0: str = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"; break;
                    case  1: str = "abcdefghijklmnopqrstuvwxyz{|}~｡｢｣､･ｦｧｨｩｪｫｬｭｮｯｰｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿ"; break;
                    case  2: str = "ﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜﾝﾞﾟ  "; break;
                    case  3: str = "ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただ"; break;
                    case  4: str = "ちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむ"; break;
                    case  5: str = "めもゃやゅゆょよらりるれろゎわゐゑをんゔゕゖ　　"; break;
                    case  6: str = "ァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダ"; break;
                    case  7: str = "チヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミム"; break;
                    case  8: str = "メモャヤュユョヨラリルレロヮワヰヱヲンヴヵヶヷヸヹヺ・ーヽヾヿ゠"; break;
                    case  9: str = "！＂＃＄％＆＇（）＊＋，－．／０１２３４５６７８９：；＜＝＞？＠"; break;
                    case 10: str = "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ［＼］＾＿｀"; break;
                    case 11: str = "ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ｛｜｝～｟｠"; break;
                }

                int count = 0;
                for (int b = 0; b < 64; ++b)
                {
                    int ID = 0;
                    int 文字長 = 0;
                    if (a <= 2)
                    {
                        if (a == 1 && b == 61){ break; }
                        if (a == 2 && b == 34){ break; }
                        GetUTFSize(str[count], 文字長);
                        ID = str[count];

                        if (文字長 > 1){ ID += str[count + 1] * 0x100; }
                        if (文字長 > 2){ ID += str[count + 2] * 0x10000; }
                        if (文字長 > 3){ ID += str[count + 3] * 0x1000000; }

                        hash[ID] = new Image(BMPフォント, { b * w/2, a * h, w / 2, h });
                        count += 文字長;
                    }
                    else
                    {
                        if (b >= 32){ break; }
                        if (a == 5 && b == 24){ break; }

                        ID = str[b * 3] + str[b * 3 + 1] * 256 + str[b * 3 + 2] * 256 * 256;
                        hash[ID] = new Image(BMPフォント, { b * w, a * h, w, h });
                    }
                }
            }
            //空白文字を登録
            hash[0x20] = new Image(BMPフォント, { 33 * w / 2, 2 * h, w / 2, h });

            //一文字ずつ
            //http://1bit.mobi/20101026101350.html 常用漢字表
            int c = 0;

            index = 0;
            int length = 0;
            if( (unsigned char)strS[0][0] == 0xEF && (unsigned char)strS[0][1] == 0xBB && (unsigned char)strS[0][2] == 0xBF ){index = 3;}

            while(1)
            {
                if( strS[0].size() <= index ){break;}

                if( (unsigned char)strS[0][index] < 0x80 )
                {
                    length = 1;
                }
                else if ( (unsigned char)strS[0][index] < 0xE0)
                {
                    length = 2; 
                }
                else if ( (unsigned char)strS[0][index] < 0xF0)
                {
                    length = 3; 
                }
                else
                {
                    length = 4;
                }
                
                SetImage(strS[0].substr(index,length).c_str(), new Image(BMPフォント, { c%32*w, (c/32+12)*h, w , h }));
                
                index += length;
                ++c;
            }


            return true;
        }

        /** 大きさを取得.*/
        int GetSize() const
        {
            return this->size;
        }

        int GetHeight() const
        {
            return this->enterHeight;
        }

        /** 描画時の幅を取得.*/
        int GetDrawStringWidth(const VariadicStream &幅を計算する文字列) const
        {
            int 最大幅 = 0;

            for (auto 文字列 : 幅を計算する文字列.StringS)
            {
                unsigned char lead;
                int charSize = 0;
                int 幅 = 0;

                for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
                {
                    lead = *it;
                    if (lead < 0x20){ charSize = 1; continue; }//制御文字は無視
                    else if (lead < 0x80){ charSize = 1; }
                    else if (lead < 0xE0){ charSize = 2; }
                    else if (lead < 0xF0){ charSize = 3; }
                    else { charSize = 4; }

                    Image* buf = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(), charSize);

                    if (buf)
                    {
                        幅 += buf->GetWidth();
                    }
                    else
                    {
                        //空白
                        幅 += size;
                    }
                }

                最大幅 = std::max(幅, 最大幅);
            }
            return 最大幅;
        }

        /** 文字を描画.*/
        /**@todo 反転描画無効*/
        bool Draw(const Point &座標, const Color &描画色, const VariadicStream &描画する文字列 , bool 右揃え = false) const override
        {
            Point 位置 = 座標;
            double x = 位置.x;

            位置.y -= differenceHeight;

            for (auto it : 描画する文字列.StringS)
            {
                if ( 右揃え)
                {
                    位置.x = x - GetDrawStringWidth(it);
                }

                DrawUTFString(位置, it, 描画色);
                位置.y += this->enterHeight;
            }

            return true;
        }

        bool DrawBold(const Point& 座標, const Color& 描画色, const Color& 縁色, const VariadicStream& 描画する文字列, bool 右揃え = false) const
        {
            Point 位置 = 座標;
            double x = 位置.x;

            位置.y -= differenceHeight;

            for (auto it : 描画する文字列.StringS)
            {
                if (右揃え)
                {
                    位置.x = x - GetDrawStringWidth(it);
                }
                位置.x++;
                DrawUTFString(位置, it, 縁色);
                位置.x--;
                位置.y++;
                DrawUTFString(位置, it, 縁色);
                位置.x--;
                位置.y--;
                DrawUTFString(位置, it, 縁色);
                位置.x++;
                位置.y--;
                DrawUTFString(位置, it, 縁色);
                位置.y++;
                DrawUTFString(位置, it, 描画色);
                位置.y += this->enterHeight;
            }

            return true;
        }

        /** 文字を影付きで描画.*/
        bool DrawShadow(const Point &座標, Color 表色, Color 影色, const VariadicStream &描画する文字列) const
        {
            Draw({ 座標.x + 1, 座標.y + 1 }, 影色, 描画する文字列);
            return Draw(座標, 表色, 描画する文字列);
        }

        /** 文字を回転して描画.*/
        /**@todo 反転描画無効*/
        bool DrawRotate(const Point &座標, double 拡大率, double 角度, const Color &描画色, const VariadicStream &描画する文字列, bool 反転フラグ = false) const override
        {
            int 行数 = (int)描画する文字列.StringS.size();

            int X補正 = int(-GetDrawStringWidth(描画する文字列) * 拡大率 * 0.5);
            int Y補正 = int(-enterHeight * 拡大率 * (0.5*行数-0.5));
            Y補正 += differenceHeight;

            for (auto it : 描画する文字列.StringS)
            {
                DrawRotateUTFString(座標, X補正, Y補正, 拡大率, 角度, it, 描画色);
                Y補正 += int(enterHeight * 拡大率);
            }

            return true;
        }

        /** 縁付き文字を回転して描画.*/
        /**@todo 反転描画無効*/
        bool DrawBoldRotate(const Point& 座標, double 拡大率, double 角度, const Color& 描画色, const Color& 縁色, const VariadicStream& 描画する文字列, bool 反転フラグ = false) const
        {
            if (角度 == 0 && 拡大率 == 0)
            {
                return DrawBold(座標,描画色,縁色, 描画する文字列);
            }

            int 行数 = (int)描画する文字列.StringS.size();

            int X補正 = int(-GetDrawStringWidth(描画する文字列) * 拡大率 * 0.5);
            int Y補正 = int(-enterHeight * 拡大率 * (0.5 * 行数 - 0.5));
            Y補正 += differenceHeight;

            for (auto& it : 描画する文字列.StringS)
            {
                DrawRotateUTFString(座標, X補正-1, Y補正-1, 拡大率, 角度, it, 縁色);
                DrawRotateUTFString(座標, X補正-1, Y補正+1, 拡大率, 角度, it, 縁色);
                DrawRotateUTFString(座標, X補正+1, Y補正-1, 拡大率, 角度, it, 縁色);
                DrawRotateUTFString(座標, X補正+1, Y補正+1, 拡大率, 角度, it, 縁色);
                DrawRotateUTFString(座標, X補正, Y補正, 拡大率, 角度, it, 描画色);
                Y補正 += int(enterHeight * 拡大率);
            }

            return true;
        }

        /** 拡大率を指定して文字を描画.*/
        /**@todo 反転描画無効*/
        bool DrawExtend(const Point &座標, double X拡大率, double Y拡大率, const Color &描画色, const VariadicStream &描画する文字列, bool 反転フラグ = false) const override
        {
            Point 位置 = 座標;
            位置.y -= differenceHeight;
            for (auto it : 描画する文字列.StringS)
            {
                DrawUTFString(位置, X拡大率, Y拡大率, it, 描画色);
                位置.y += this->enterHeight * Y拡大率;
            }

            return true;
        }

        /** 指定した文字に対応するImageを設定.*/
        /** 文字列が2文字以上なら2文字目以降は無視*/
        void SetImage(const std::string &文字, Image *対応画像)
        {
            if (Loading::isLoading)
            {
                Loading::AddLoading([=]{ SetImage(文字,対応画像); });
                return;
            }

            int charSize;
            auto it = 文字.begin();

            if (!GetUTFSize(*it, charSize)){ return; }
            SetHash(文字.substr(std::distance(文字.begin(), it), charSize).c_str(), charSize, 対応画像);
        }

        Image* GetImage(const std::string& 文字)
        {
            auto it = 文字.begin();
            unsigned char lead;
            int charSize = 0;

            lead = *it;
            if (lead < 0x20) { return nullptr; }//制御文字は無視
            else if (lead < 0x80) { charSize = 1; }
            else if (lead < 0xE0) { charSize = 2; }
            else if (lead < 0xF0) { charSize = 3; }
            else { charSize = 4; }

            Image* buf = GetHash(文字.substr(std::distance(文字.begin(), it), charSize).c_str(), charSize);


            return buf;
        }

        /** 指定した文字から連続してに対応するImageをまとめて設定.*/
        /** 例えば文字列="0"で登録数=10なら0～9までを登録*/
        /** アルファベットや数字用*/
        void SetImageS(const std::string &文字列, ImagePack *対応画像, int 登録数)
        {
            if (Loading::isLoading)
            {
                Loading::AddLoading([=]{ SetImageS(文字列, 対応画像,登録数); });
                return;
            }

            int charSize;

            auto it = 文字列.begin();
            if (!GetUTFSize(*it, charSize)){ return; }
            std::string str = 文字列.substr(0, charSize);
                
            for (int a = 0; a < 登録数;++a)
            {
                if (!GetUTFSize(*it, charSize)){ continue; }
                SetHash(str.c_str(),charSize,対応画像[0][a]);
                if (str[charSize - 1] == 0xff)
                {
                    str[charSize - 2]++;
                    str[charSize - 1] = 0;
                }
                else
                {
                    str[charSize - 1]++;
                }
            }
        }
    };
}