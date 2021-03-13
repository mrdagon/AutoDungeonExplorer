//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
//#include <Tiled/GUIData.h>
//#include <Tiled/TmxToGUI.h>
#include <Tiled/GetTag.h>
#include <Multimedia/File.h>
#include <map>
#include <vector>

namespace SDX
{
	struct ClassTemplate
	{
		std::string name;//class名
		bool isTile = false;
		std::vector<std::string> proNameS;//プロパティ名
		std::vector<std::string> proTypeS;//プロパティ型
		std::map<std::string,std::string> codeS;//各種コード
	};

	struct GUI_Scene
	{
		std::string name;//class名

		struct GUI
		{
			GUI(const std::string& name, const std::string& type , int id , const Rect& rect, int gID, double zoomW, double zoomH, double angle) :
				name(name),
				type(type),
				rect(rect),
				id(id),
				gID(gID),
				zoomW(zoomW),
				zoomH(zoomH),
				angle(angle),
				isTile(gID != 0)
			{}

			std::string name;//変数名
			std::string type;//型名
			Rect rect;//座標＆大きさ
			double angle;
			double zoomW;
			double zoomH;
			bool isTile;//gIDパラメータの有無
			int id;
			int gID;
			std::vector<std::string> propertieS;
			std::map<std::string, std::string> codeS;//各種コード
		};

		std::vector<GUI> guiS;
	};

	struct TiledChip
	{
		int w;
		int h;
		std::string name;
		int no = -1;

		TiledChip(int w,int h , const std::string name = "" , int no = -1):
			w(w),
			h(h),
			name(name),
			no(no)
		{}

	};

	/**@と<>を差し替えて、tabを挿入する.*/
	void ReplaceTag(std::string &変換文字 , std::string &置き換え文字)
	{
		int num;
		while (1)
		{
			num = 変換文字.find("@");
			if (num == std::string::npos){ break; }
			if (置き換え文字 == "")
			{
				変換文字.erase(num, 1);
			}
			else
			{
				変換文字.replace(num, 1, 置き換え文字);		
			}
		}
		while (1)
		{
			num = 変換文字.find("&lt;");//<
			if (num == std::string::npos){ break; }
			変換文字.replace(num, 4, "<");
		}
		while (1)
		{
			num = 変換文字.find("&gt;");//<
			if (num == std::string::npos){ break; }
			変換文字.replace(num, 4, ">");
		}

		変換文字.insert(0, "\t\t\t");

	}

	void MakeFactoryCode(std::vector<std::string> &classNameS, std::map<std::string, ClassTemplate> &classS, const std::string& クラス名プリフィックス, const char* 名前空間名)
	{
		//Factoryの生成
		File file("GUI_Factory.h", FileMode::Write);

		file.AddLine("#pragma once");
		file.AddLine("#include <Tiled/GUIData.h>");
		file.AddLine("#include <vector>");
		file.AddLine("#include <string>");
		for (auto &it : classNameS)
		{
			file.AddLine({ "#include \"", クラス名プリフィックス + classS[it].name, ".h\"" });
		}
		file.AddLine("");
		file.AddLine({ "namespace " , 名前空間名 });
		file.AddLine("{");
		file.AddLine("using namespace SDX;");
		file.AddLine("\tvoid GUI_Factory(GUIData& data, std::string& type , int id , int gid, Rect rect, double zoomW , double zoomH , double angle, std::vector<std::string>& properties)");
		file.AddLine("\t{");
		int index = 0;
		for (auto &it : classNameS)
		{
			if (index == 0)
			{
				file.AddLine({ "\t\tif(type == \"", it, "\")" });
			}
			else
			{
				file.AddLine({ "\t\telse if(type == \"", it, "\")" });
			}
			file.AddLine("\t\t{");
			std::string str = "\t\t\tdata.dataS.push_back(std::make_shared<" + クラス名プリフィックス + it + ">(id,rect,angle";
			if (classS[it].isTile)
			{
				str += ",gid,zoomW,zoomH";
			}
			int num = 0;
			for (auto & it : classS[it].proTypeS)
			{
				if (it == "std::string")
				{
					str += ",properties[" + std::to_string(num) + "].c_str()";
				}
				else if (it == "double")
				{
					str += ",std::atof(properties[" + std::to_string(num) + "].c_str())";
				}
				else
				{
					str += ",std::atoi(properties[" + std::to_string(num) + "].c_str())";
				}
				++num;
			}
			str += "));";
			file.AddLine(str);
			file.AddLine("\t\t}");
			++index;
		}

		file.AddLine("\t}");
		file.AddLine("}");
		file.Close();

	}

	void MakeClassCode(const char* templateClass, std::vector<std::string> &classNameS, std::map<std::string, ClassTemplate> &classS, const std::string& クラス名プリフィックス, const char* 名前空間名)
	{
		//各クラスのコード
		File file(templateClass, FileMode::Read);
		auto defstrS = file.GetLineS();
		std::vector<std::string> strS;
		bool isWrite;

		for (auto &itt : classNameS)
		{
			ClassTemplate& cls = classS[itt];
			isWrite = true;

			File tempFile((クラス名プリフィックス + itt + ".h").c_str(), FileMode::Read);
			if (tempFile.GetFileMode() != FileMode::None)
			{
				//既に存在する場合はそれを更新
				strS = tempFile.GetLineS();
			}
			else
			{
				strS = defstrS;
			}
			tempFile.Close();

			File classFile((クラス名プリフィックス + itt + ".h").c_str(), FileMode::Write);

			for (auto &it : strS)
			{
				if (it.find("NAMESPACE") != std::string::npos)
				{
					std::string buf = it;
					int num = buf.find("NAMESPACE");
					buf.erase(num, 9);
					buf.insert(num, 名前空間名);
					classFile.AddLine(buf);
				}
				else if (it.find("CLASSNAME") != std::string::npos)
				{
					std::string buf = it;
					int num = buf.find("CLASSNAME");
					buf.erase(num, 9);
					buf.insert(num, クラス名プリフィックス + cls.name);
					classFile.AddLine(buf);
				}
				else if (it.find("@メンバー宣言") != std::string::npos)
				{
					isWrite = false;
					classFile.AddLine(it);
					if ( cls.isTile)
					{
						classFile.AddLine({ "\t\tint gID;" });
						classFile.AddLine({ "\t\tdouble zoomW;" });
						classFile.AddLine({ "\t\tdouble zoomH;" });
					}
					for (unsigned int a = 0; a < cls.proNameS.size();++a)
					{
						classFile.AddLine({ "\t\t", cls.proTypeS[a] , " ", cls.proNameS[a] , ";" });
					}
				}
				else if (it.find("@コンストラクタ") != std::string::npos)
				{
					isWrite = false;
					std::string str = "\t\t";
					str += クラス名プリフィックス + cls.name + "( int id , const Rect& rect, double angle";
					if ( cls.isTile )
					{
						str += ",int gID";
						str += ",double zoomW";
						str += ",double zoomH";
					}
					for (unsigned int a = 0; a < cls.proNameS.size(); ++a)
					{
						str += ",";
						if (cls.proTypeS[a] == "std::string")
						{
							str += "const char* " + cls.proNameS[a];
						}
						else
						{
							str += cls.proTypeS[a] + " " + cls.proNameS[a];
						}
					}
					str += "):";

					classFile.AddLine(it);
					classFile.AddLine(str);
					for (unsigned int a = 0; a < cls.proNameS.size(); ++a)
					{
						classFile.AddLine({ "\t\t\t", cls.proNameS[a], "(", cls.proNameS[a], ")," });
					}
					if (cls.isTile)
					{
						classFile.AddLine({ "\t\t\tgID(gID)," });
						classFile.AddLine({ "\t\t\tzoomW(zoomW)," });
						classFile.AddLine({ "\t\t\tzoomH(zoomH)," });

					}
					classFile.AddLine({ "\t\t\tIGUI(id,rect,angle)" });
					classFile.AddLine({ "\t\t", "{}" });
				}
				else if (it.find("//@End") != std::string::npos)
				{
					classFile.AddLine(it);
					isWrite = true;
				}
				else if (it.find("//@") != std::string::npos)
				{
					std::string name = it.substr(it.find("//@")+3);

					classFile.AddLine(it);//@の部分をコピー
					isWrite = false;
					
					std::string buf = cls.codeS[name];
					ReplaceTag(buf, std::string(""));
					classFile.AddLine( buf );
				}
				else if (isWrite)
				{
					classFile.AddLine(it);
				}
			}
		}

	}

	void MakeSceneCode(const char* templateScene, std::vector<std::string> &classNameS, std::map<std::string, ClassTemplate> &classS, std::vector<GUI_Scene> &sceneS, const char* tmxFile, const std::string& クラス名プリフィックス, const char* 名前空間名)
	{
		File file(templateScene, FileMode::Read);
		auto defstrS = file.GetLineS();
		std::vector<std::string> strS;// = file.GetLineS();

		bool isWrite = true;

		for (auto &scene : sceneS)
		{
			File prevFile((scene.name + ".h").c_str(), FileMode::Read);

			if (prevFile.GetFileMode() == FileMode::Read)
			{
				strS = prevFile.GetLineS();
			}
			else
			{
				strS = defstrS;
			}
			prevFile.Close();

			File sceneFile((scene.name + ".h").c_str(), FileMode::Write);

			isWrite = true;

			for (auto &str : strS)
			{
				if (str.find("NAMESPACE") != std::string::npos)
				{
					std::string buf = str;
					int num = buf.find("NAMESPACE");
					buf.erase(num, 9);
					buf.insert(num, 名前空間名);
					sceneFile.AddLine(buf);
				}
				else if(str.find("CLASSNAME") != std::string::npos)
				{
					int num = str.find("CLASSNAME");
					std::string buf = str;
					buf.replace(num, 9, scene.name);
					sceneFile.AddLine(buf);
				}
				else if (str.find("@Define") != std::string::npos)
				{
					isWrite = false;
					sceneFile.AddLine(str);
					
					for (auto &gui : scene.guiS)
					{
						std::string buf = "\t\t";
						buf += クラス名プリフィックス + gui.type + " " + gui.name + " = { " + std::to_string(gui.id) + ", {";
						buf += std::to_string(int(gui.rect.x)) + ",";
						buf += std::to_string(int(gui.rect.y)) + ",";
						buf += std::to_string(int(gui.rect.GetW())) + ",";
						buf += std::to_string(int(gui.rect.GetH())) + "} , ";
						buf += std::to_string(gui.angle);

						if (gui.isTile)
						{
							buf += ",";
							buf += std::to_string(gui.gID);
							buf += ",";
							buf += std::to_string(gui.zoomW);
							buf += ",";
							buf += std::to_string(gui.zoomH);
						}

						int index = 0;

						for (auto &pro : gui.propertieS)
						{
							if (classS[gui.type].proTypeS[index] == "std::string")
							{
								buf += ",\"";
								buf += pro + "\"";
							}
							else
							{
								buf += ",";
								buf += pro;
							}

							++index;
						}

						buf += "};";
	
						sceneFile.AddLine(buf);
					}
				}
				else if (str.find("@Load") != std::string::npos)
				{
					std::string fileName = tmxFile;
					fileName = fileName.substr( fileName.find_last_of("\\") + 1 );

					isWrite = false;
					sceneFile.AddLine(str);
					sceneFile.AddLine({ "\t\t\tSDX::GUIData guiData = SDX::TMXtoGUI( TMX_FILE_NAME , \"", scene.name, "\", GUI_Factory);", });
					sceneFile.AddLine("");

					int index = 0;
					for (auto &gui : scene.guiS)
					{
						sceneFile.AddLine({ "\t\t\t", gui.name, " = *dynamic_cast<", クラス名プリフィックス + gui.type, "*>(guiData.dataS[", index, "].get());" });
						++index;
					}
				}
				else if (str.find("@End") != std::string::npos)
				{
					isWrite = true;
					sceneFile.AddLine(str);
				}
				else if (str.find("//@") != std::string::npos && str.find("@todo") == std::string::npos)
				{
					//@todoタグは無視
					std::string name = str.substr(str.find("//@")+3);

					isWrite = false;
					sceneFile.AddLine(str);//@nameを挿入

					for (auto &gui : scene.guiS)
					{
						std::string buf = classS[gui.type].codeS[name];
						if (buf == "" ){ continue; }
						ReplaceTag(buf, gui.name + ".");
						sceneFile.AddLine(buf);
					}

				}
				else if (isWrite)
				{
					sceneFile.AddLine(str);
				}
			}
			file.Close();
		}
	}

	void MakeEnumCode(const char* templateEnum, std::vector<GUI_Scene> &sceneS, std::vector<TiledChip> &tileS, const char* 名前空間名)
	{
		//オブジェクトIDを列挙型で出力
		File file("UI_Enum.h", FileMode::Write);
		File temp( templateEnum , FileMode::Read);

		auto strS = temp.GetLineS();

		for (auto &str : strS)
		{
			if (str.find("NAMESPACE") != std::string::npos)
			{
				std::string buf = str;
				int num = buf.find("NAMESPACE");
				buf.erase(num, 9);
				buf.insert(num, 名前空間名);
				file.AddLine(buf);
			}
			else if (str.find("@Enum") != std::string::npos)
			{
				for (auto& scene : sceneS)
				{
					for (auto &gui : scene.guiS)
					{
						if (gui.name != "")
						{
							file.AddLine({ "\t\t",scene.name , "_" , gui.name, " = ", gui.id, "," });
						}
					}
				}
			}
			else if (str.find("@Resource") != std::string::npos)
			{
				int index = 0;
				for (auto& tile : tileS)
				{
					if (tile.name != "")
					{
						std::string str = tile.name;
						if (tile.no >= 0)
						{
							str += "_";
							str += std::to_string(tile.no);
						}

						file.AddLine({ "\t\t", str , " = ", index , "," });
					}
					++index;
				}
			}
			else
			{
				file.AddLine(str);
			}
		}
	}

	/**tmxファイルとテンプレートからコードを生成する*/
	void TMXtoCode(const char* tmxFile, const char* templateClass, const char* templateScene, const char* templateEnum, const char* クラス名プリフィックス , const char* 名前空間名 )
	{
		//まず内部データに変更
		//その後、クラス情報を取得、その後各クラスのコード、GUI_Factoryのコード、
		File file(tmxFile, FileMode::Read);
		std::vector<std::string> strS = file.GetLineS();
		file.Close();

		std::map<std::string, ClassTemplate> classS;
		std::vector<std::string> classNameS;
		std::vector<GUI_Scene> sceneS;
		std::vector<TiledChip> tileS;
		
		tileS.push_back({ 0, 0 });//gID = 0は空データ
		std::string nowClass;

		bool isTemplate = false;//テンプレートレイヤーか否か
		int tileW;
		int tileH;

		for (auto &it : strS)
		{
			if (it.find("<tileset") != std::string::npos)
			{
				tileW = std::atoi(GetTag(it, "tilewidth=").c_str());
				tileH = std::atoi(GetTag(it, "tileheight=").c_str());
			}
			else if (it.find("<image width") != std::string::npos)
			{
				std::string name = GetTag(it, "source=");
				name = name.substr( name.find("/") + 1);
				name = name.substr(0, name.find("."));

				while ( name.find("/") != std::string::npos)
				{
					name = name.replace(name.find("/"), 1, "_");
				}
				tileS.push_back({ std::atoi(GetTag(it, "width=").c_str()) , std::atoi(GetTag(it, "height=").c_str()) , name});				
			}
			else if (it.find("<image source") != std::string::npos)
			{
				std::string name = GetTag(it, "source=");
				name = name.substr(name.find("/") + 1);
				name = name.substr(0, name.find("."));
				while (name.find("/") != std::string::npos)
				{
					name = name.replace(name.find("/") + 1, 1, "_");
				}

				int w = std::atoi(GetTag(it, "width=").c_str()) / tileW;
				int h = std::atoi(GetTag(it, "height=").c_str()) / tileH;

				for (int a = 0; a < w*h; ++a)
				{
					tileS.push_back({ tileW, tileH ,name , a});
				}
			}
			else if (it.find("\"TEMPLATE\"") != std::string::npos)
			{
				isTemplate = true;
			}
			else if (it.find("<objectgroup") != std::string::npos)
			{
				isTemplate = false;
				nowClass = GetTag(it,"name=");

				sceneS.push_back(GUI_Scene());
				sceneS.back().name = nowClass;
			}
			else if (it.find("<object id=") != std::string::npos)
			{
				if ( isTemplate )
				{
					nowClass = GetTag(it, "name=");
					classS[nowClass].name = nowClass;
					classNameS.push_back(nowClass);
				}
				else
				{		
					std::string name = GetTag(it,"name=");
					std::string type = GetTag(it, "type=");
					if (type == "0"){ type = "Image"; }

					Rect rect;
					double angle;
					double zoomW = 1;
					double zoomH = 1;
					int id,gid;
					id = std::atoi(GetTag(it, " id=").c_str());
					gid = std::atoi(GetTag(it, "gid=").c_str());
					rect.x = std::atoi(GetTag(it, "x=").c_str());//四角形は左上、画像は左下
					rect.y = std::atoi(GetTag(it, "y=").c_str());	
					rect.widthRight = std::atoi(GetTag(it, "width=").c_str());
					rect.heightDown = std::atoi(GetTag(it, "height=").c_str());
					angle = std::atoi(GetTag(it, "rotation=").c_str());

					if (gid != 0)
					{
						//座標は画像の左下が基準になる、回転させると座標も変化する
						//中心座標に変換
						//角度は時計回りで-180～180
						classS[type].isTile = true;
						rect.y -= tileS[gid].h;
						if (rect.widthRight > 0){ zoomW = rect.widthRight; }
						if (rect.heightDown > 0){ zoomH = rect.heightDown; }
						rect.widthRight = tileS[gid].w * zoomW;
						rect.heightDown = tileS[gid].h * zoomH;
					}					

					sceneS.back().guiS.push_back(GUI_Scene::GUI(name, type, id , rect, gid, zoomW, zoomH, angle));
				}

			}
			else if (it.find("<property name") != std::string::npos)
			{
				if ( isTemplate )
				{
					std::string name = GetTag(it,"name=");
					std::string value = GetTag(it, "value=");

					if (name.find("~") != std::string::npos)
					{
						//各種コード ~は無視する
						classS[nowClass].codeS[name.substr(1)] = value;
					}
					else
					{
						classS[nowClass].proNameS.push_back(GetTag(it, "name="));
						classS[nowClass].proTypeS.push_back(GetTag(it, "value="));
					}
				}
				else
				{
					std::string name = GetTag(it, "name=");
					std::string value = GetTag(it, "value=");

					if (name.find("~") != std::string::npos)
					{
						//コード ~は無視する
						sceneS.back().guiS.back().codeS[name.substr(1)] = value;
					}
					else
					{
						//値の場合
						sceneS.back().guiS.back().propertieS.push_back(GetTag(it, "value="));
					}
				}
			}
		}
		 
		MakeFactoryCode(classNameS, classS , クラス名プリフィックス,名前空間名);
		MakeClassCode(templateClass, classNameS, classS, クラス名プリフィックス, 名前空間名);
		MakeSceneCode(templateScene, classNameS, classS, sceneS, tmxFile, クラス名プリフィックス, 名前空間名);
		MakeEnumCode(templateEnum, sceneS, tileS, 名前空間名);
	}
}