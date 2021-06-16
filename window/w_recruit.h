//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

#pragma warning( disable : 4996 )
#include <codecvt>

namespace SDX_ADE
{
	using namespace SDX;



	/*求人ウィンドウ*/
	class W_Recruit : public UIWindow
	{
	private:
		class UI名前 : public UIObject
		{
		public:
			void Draw派生() override
			{
				//名前と入力状態の表示
				DrawUI(UIType::グループ暗,Design::Base);

				//MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 枠No, 凹み);
				//MSystem::DrawWindow({ px + Lp(30)     , py + Lp(31) }, Lp(32), Lp(33), 12);

				W_Recruit::This->名前更新();

				//現在の名前を表示
				if (W_Recruit::This->is名前入力中)
				{
					std::wstring wstr = W_Recruit::This->入力中文字;//確定状態の文字

					wstr.insert(W_Recruit::This->挿入位置, L"|");//二バイト文字にして入力位置に|を挿入
					wstr.insert(W_Recruit::This->挿入位置, W_Recruit::This->conv.from_bytes(System::textComposition));//入力中の文字を挿入

					std::string str = W_Recruit::This->conv.to_bytes(wstr);//マルチバイト文字に変換

					//挿入中の文字の座標を計算
					int W変換中文字 = MFont::L->GetDrawStringWidth(System::textComposition);
					auto sstr = W_Recruit::This->conv.to_bytes(W_Recruit::This->入力中文字.substr(0, W_Recruit::This->挿入位置));
					int X変換中文字 = MFont::L->GetDrawStringWidth(sstr.c_str());

					Drawing::Rect({ GetX() + layout->並べx + X変換中文字 + 4 , GetY() + layout->並べy - 2 , W変換中文字 , 32 }, Color::White );
					MFont::L->DrawBold({ GetX() + layout->並べx + 4,GetY() + layout->並べy }, Color::White, Color::Black, { str.c_str() });
				}
				else {
					MFont::L->DrawBold({ GetX() + layout->並べx + 4, GetY() + layout->並べy }, Color::White, Color::Black, { W_Recruit::This->求人名前 });
				}


				W_Recruit::This->名前入力();
			}
		};

		class UI説明 : public UIObject
		{
		public:
			//職業名
			//装備アイコン
			//概説
			//分割線
			//職業詳細説明文
			//職業イラスト
			void Draw派生() override
			{
				auto& posA = Layout::Data(LReqruit::職業名);
				auto& posB = Layout::Data(LReqruit::装備アイコン);
				auto& posC = Layout::Data(LReqruit::職業概要);
				auto& posD = Layout::Data(LReqruit::分割線);
				auto& posE = Layout::Data(LReqruit::職業説明文);
				auto& posF = Layout::Data(LReqruit::職業イラスト);

				auto job = &ExplorerClass::data[W_Recruit::This->表示職業];

				DrawUI(UIType::グループ暗);

				//ジョブ名
				MFont::M->DrawBoldRotate({ GetX() + posA.x ,GetY() + posA.y }, 1, 0, Color::White, Color::Black, job->名前, false);
				//ジョブ装備種
				job->初期装備[0]->image->DrawRotate({ GetX() + posB.x ,GetY() + posB.y },1,0);

				//一行説明
				MFont::M->DrawBold({ GetX() + posC.x ,GetY() + posC.y }, Color::White, Color::Black, job->概説, false);

				//区切り線
				Drawing::Line({ GetX() + posD.x ,GetY() + posD.y }, { GetX() + posD.x + posD.w ,GetY() + posD.y + posD.h }, Color::White, 1);

				//ジョブ説明
				MFont::M->DrawBold({ GetX() + posE.x ,GetY() + posE.y }, Color::White, Color::Black, { job->説明 });

				//立ち絵
				MJob::立ち絵[job->ID].DrawRotate({ GetX() + posF.x ,GetY() + posF.y }, 2, 0);

				W_Recruit::This->表示職業 = W_Recruit::This->選択職業;
			}
		};

		class UI職業 : public UIObject
		{
		public:
			//選択中は明るい、マウスオーバーでやや明るい
			void Draw派生() override
			{
				UIType ui_now = UIType::丸フレーム;
				if (lineID == W_Recruit::This->選択職業 || isOver == true)
				{
					//選択中は暗い
					ui_now = UIType::選択丸フレーム;
				}

				DrawUI( ui_now , Design::Base);

				auto job = &ExplorerClass::data[lineID];

				auto& posA = Layout::Data(LReqruit::職一覧名前);
				auto& posB = Layout::Data(LReqruit::職一覧アイコン);

				//職業ちびどっと
				job->ちびimage[0][1]->DrawRotate({ GetX() + posA.x , GetY() + posA.y }, 2, 0);
				//職業名
				MFont::L->DrawRotate({ GetCenterX() + posB.x ,GetCenterY() + posB.y } , 1, 0 ,Color::Black , { job->名前 });
			}

			void Click() override
			{
				W_Recruit::This->選択職業 = lineID;
				W_Recruit::This->表示職業 = lineID;
				MSound::効果音[SE::決定].Play();
			}

			void Over() override
			{
				W_Recruit::This->表示職業 = lineID;
			}

		};

	public:
		static W_Recruit* This;
		inline static std::string 求人名前;
		inline static ID_Job 選択職業;

		int 表示職業;

		UI名前 名前入力欄;
		UI説明 説明;
		std::vector<UI職業> 職業;

		UITextFrame 一覧枠;

		UIButton ランダム名ボタン;
		UIButton 名前変更ボタン;
		UIButton 登録ボタン;

		//名前入力用変数
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;//入力を変換する
		bool is名前入力中 = false;
		int 挿入位置 = 0;
		std::wstring 入力中文字;
		bool is確定前 = false;

		void Init()
		{
			This = this;

			Set(WindowType::Recruit, IconType::求人);
			SetPos(LReqruit::ウィンドウ, true, false, true);

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			表示職業 = 0;
			//●初期化
			職業.resize(ExplorerClass::data.size());
			int a = -1;

			名前入力欄.SetUI(LReqruit::名前枠);
			説明.SetUI(LReqruit::説明枠);
			for (auto& it : ExplorerClass::data)
			{
				a++;
				職業[a].SetUI(LReqruit::職一覧, a, &一覧枠);
			}

			一覧枠.SetUI(LReqruit::職一覧枠,"");
			ランダム名ボタン.SetUI(LReqruit::ランダムボタン, &MIcon::UI[IconType::再募集] );
			名前変更ボタン.SetUI(LReqruit::名前変更ボタン, &MIcon::UI[IconType::ログ] );
			登録ボタン.SetUI(LReqruit::登録ボタン , "採用");

			//●イベント
			ランダム名ボタン.clickEvent = [&]()
			{
				is名前入力中 = false;
				求人名前 = "ランダム";
			};
			名前変更ボタン.clickEvent = [&]() {名前入力開始完了(); };
			名前入力欄.clickEvent = [&]() {名前入力開始完了(); };
			登録ボタン.clickEvent = [&]()
			{
				//空きがあって編成中のパーティか、控えに追加
				名前確定();
				Guild::P->探索者登録(選択職業, 求人名前);
				MSound::効果音[SE::決定].Play();
				is表示 = false;
			};

			//●登録
			item.clear();
			AddItem(名前入力欄);
			AddItem(ランダム名ボタン);
			AddItem(名前変更ボタン);
			AddItem(登録ボタン);
			AddItem(説明);
			AddItem(職業);
			AddItem(一覧枠);			
		}

		void Update()
		{
			SetPos(LReqruit::ウィンドウ, true, false, true);
			名前更新();
		}

		void 名前確定()
		{
			if (!is名前入力中) { return; }

			W_Recruit::This->求人名前 = conv.to_bytes(入力中文字);

			is名前入力中 = false;
			MSound::効果音[SE::決定].Play();
		}

		void 名前更新()
		{
			if (System::inputText.size() > 0)
			{
				入力中文字.insert(挿入位置, conv.from_bytes(System::inputText));
				挿入位置 += (int)conv.from_bytes(System::inputText).size();
				System::inputText = "";
				is確定前 = true;
			}
		}

		void 名前入力()
		{
			if (!is名前入力中) { return; }

			if (Input::key.Return.on)
			{
				if (is確定前)
				{
					is確定前 = false;
				}
				else {
					名前確定();
					return;
				}
			}
			static int 入力中文字数 = 1;
			static bool is変換中 = false;

			//以下は変換前文字がある場合処理しない
			if (入力中文字数 > 0)
			{
				is変換中 = true;
				入力中文字数 = (int)System::textComposition.size();
				return;
			}

			if (is変換中 == true)
			{
				is変換中 = false;
				return;
			}

			入力中文字数 = (int)System::textComposition.size();

			if ( Input::key.Back.IsPush(30,5) && 挿入位置 > 0)
			{
				入力中文字.erase(挿入位置 - 1, 1);
				挿入位置--;
			}
			if (Input::key.Delete.IsPush(30, 5) && 挿入位置 < (int)入力中文字.size())
			{
				入力中文字.erase(挿入位置, 1);
			}

			if (Input::key.Left.IsPush(30, 5) )
			{
				挿入位置 = std::max(挿入位置 - 1, 0);
			}
			if (Input::key.Right.IsPush(30, 5) )
			{
				挿入位置 = std::min(挿入位置 + 1, (int)入力中文字.size());
			}



		}

		void 名前入力開始完了()
		{
			if (is名前入力中)
			{
				名前確定();
			}
			else
			{
				入力中文字 = conv.from_bytes(求人名前);//2byte幅固定文字に変換
				挿入位置 = (int)入力中文字.size();
				is名前入力中 = true;
				MSound::効果音[SE::決定].Play();
			}
		}

	};

	W_Recruit* W_Recruit::This;
}