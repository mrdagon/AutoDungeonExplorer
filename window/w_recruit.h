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
	class W_Recruit: public UIWindow
	{
	private:	
		class GUI_名前変更 :public GUI_Object
		{
		public:
			W_Recruit* 親;

			void Draw派生(double px, double py)
			{
				//名前変更ボタンを表示
				int 枠No = (親->is名前入力中) ? (2) : (0);
				int 凹み = (親->is名前入力中) ? (-1) : (1);

				MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 枠No , 凹み);
				MSystem::DrawWindow({ px + Lp(30)     , py + Lp(31) }, Lp(32), Lp(33), 12 );

				親->名前更新();

				//現在の名前を表示
				if(親->is名前入力中 )
				{
					std::string str;
					std::wstring wstr = 親->入力中文字;

					wstr.insert(親->挿入位置,L"|");
					wstr.insert(親->挿入位置, 親->conv.from_bytes(System::textComposition));
					
					str = 親->conv.to_bytes(wstr);

					int W変換中文字 = MFont::MAlias.GetDrawStringWidth(System::textComposition);
					auto sstr = 親->conv.to_bytes(親->入力中文字.substr(0, 親->挿入位置));
					int X変換中文字 = MFont::MAlias.GetDrawStringWidth(sstr.c_str());

					Drawing::Rect({ px + Lp(34) + X変換中文字 , py + Lp(35) , W変換中文字 , 20 }, Color::Red);
					MFont::MAlias.DrawBold({ px + Lp(34),py + Lp(35) }, Color::White, Color::Black, { str.c_str() });
				}else{
					MFont::MAlias.DrawBold({ px + Lp(34),py + Lp(35) }, Color::White, Color::Black, { Guild::P->求人名前 });
				}

				//変更ボタンのアイコン
				MIcon::UI[IconType::ログ].DrawRotate({ px + Lp(36) , py + Lp(37) }, 2, 0);

				親->名前入力();
			}

			void Click(double px, double py)
			{
				//ポップアップウィンドウで名前入力-未実装
				if (親->is名前入力中)
				{
					親->名前確定();
				} else {
					親->入力中文字 = 親->conv.from_bytes(Guild::P->求人名前);
					親->挿入位置 = (int)親->入力中文字.size();
					親->is名前入力中 = true;
					CSV::isDebugInput = false;
					MSound::効果音[SE::決定].Play();
				}
			}


		};

		class GUI_職業選択 : public GUI_Object
		{
		public:
			ID_Job 職業;

			GUI_職業選択(ID_Job 職業):
				職業(職業)
			{}

			void Draw派生(double px, double py)
			{
				auto job = &ExplorerClass::data[職業];
				//選択中は枠の色を変える			
				MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), (職業 == Guild::P->求人職業) ? (10) : (11) );
				//職業見た目
				job->ちびimage[0][1]->DrawRotate({ px + Lp(38) ,py + Lp(39) }, 2, 0);
				//職業名表示、職業番号表示、職業説明
				MFont::MAlias.DrawBold({ px + Lp(40),py + Lp(41) }, Color::White, Color::Black, { job->名前 });
			}

			void Click(double px, double py)
			{
				Guild::P->求人職業 = 職業;
				MSound::効果音[SE::決定].Play();
			}
		};

		class GUI_職業説明枠 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				auto job = &ExplorerClass::data[Guild::P->求人職業];

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);

				//ジョブ名
				MFont::MAlias.DrawBoldRotate({ px + Lp(42) ,py + Lp(43) }, 1, 0, Color::White, Color::Black, job->名前, false);
				//ジョブ装備種
				//MIcon::アイテム[job->初期装備[0]->見た目].DrawRotate({px + Lp(44) ,py + Lp(45) },1,0);

				//推奨隊列
				MFont::MAlias.DrawBold({ px + Lp(46) ,py + Lp(47) }, Color::White, Color::Black, job->概説 , false);
				//区切り線
				Drawing::Line({ px + Lp(48), py + +Lp(50) }, { px + Lp(49), py + +Lp(50) }, Color::White, 1);

				//ジョブ説明
				MFont::MAlias.DrawBold({ px + Lp(51),py + Lp(52) }, Color::White, Color::Black, { job->説明 });

				//立ち絵
				MJob::立ち絵[job->ID].DrawRotate({ px + Lp(56),py + Lp(57) }, 2, 0);
			}
		};

		class GUI_採用 :public GUI_Object
		{
		public:
			W_Recruit* 親;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 0 , 1);

				//採用の文字
				MFont::MAlias.DrawBoldRotate({ px + Lp(53),py + Lp(54) }, 1, 0, Color::White, Color::Black, { TX::Recruit_採用 });
			}

			void Click(double px, double py)
			{
				//空きがあって編成中のパーティか、控えに追加
				親->名前確定();
				Guild::P->求人採用();
				MSound::効果音[SE::決定].Play();
				親->is表示 = false;
			}
		};

		class GUI_ランダム :public GUI_Object
		{
		public:
			W_Recruit* 親;
			int 連打 = 0;

			void Draw派生(double px, double py)
			{
				連打--;
				int n = (連打 <= 0) ? (0) : (1);
				//枠の描画
				MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), n, 1 - n * 2);
				//ランダムのアイコン
				MIcon::UI[IconType::再募集].DrawRotate({ px + Lp(36) , py + Lp(37) }, 2, 0);
			}

			void Click(double px, double py)
			{
				//求人設定ランダム化
				if (親->is名前入力中)
				{
					連打 = 10;
				}

				if (連打 > 0) { return; }
				連打 = 10;
				親->is名前入力中 = false;
				CSV::isDebugInput = true;
				Guild::P->求人リロール();
				MSound::効果音[SE::決定].Play();
			}
		};

	public:
		GUI_名前変更 名前変更;
		GUI_ランダム ランダム;//名前ランダムボタン
		GUI_Frame 職業枠;
		std::vector<GUI_職業選択> 職業;
		GUI_採用 採用;
		GUI_職業説明枠 職業説明枠;

		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
		bool is名前入力中 = false;
		int 挿入位置 = 0;
		std::wstring 入力中文字;
		bool is変換 = false;

		void Init()
		{
			種類 = WindowType::Recruit;

			アイコン = IconType::求人;
			横幅 = 280;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 180;
			縦内部幅 = 180;//120xランク数
			スクロール位置 = 0;
			isスクロールバー表示 = false;

			名前変更.親 = this;
			ランダム.親 = this;
			採用.親 = this;

			職業.reserve((int)ExplorerClass::data.size());
			for (int a = 0; a < (int)ExplorerClass::data.size(); a++)
			{
				職業.emplace_back(a);
			}

			職業枠.text = "Job";
		}

		void GUI_Update()
		{

		}

		void 名前確定()
		{
			if (!is名前入力中) { return; }

			Guild::P->求人名前 = conv.to_bytes(入力中文字);

			is名前入力中 = false;
			CSV::isDebugInput = true;

			MSound::効果音[SE::決定].Play();			

		}

		void 名前更新()
		{
			if (System::inputText.size() > 0)
			{
				入力中文字.insert(挿入位置, conv.from_bytes(System::inputText));
				挿入位置 += (int)conv.from_bytes(System::inputText).size();
				System::inputText = "";
				is変換 = true;
			}
		}

		void 名前入力()
		{
			if (!is名前入力中) { return; }

			if (Input::key.Return.on)
			{
				if (is変換)
				{
					is変換 = false;
				} else {
					名前確定();
					return;
				}
			}
			static int 入力中文字数 = 1;

			//以下は変換前文字がある場合処理しない
			if (入力中文字数 > 0)
			{
				入力中文字数 = (int)System::textComposition.size();
				return;
			}
			入力中文字数 = (int)System::textComposition.size();
			
			if ( Input::key.Back.on && 挿入位置 > 0)
			{
				入力中文字.erase(挿入位置 - 1, 1);
				挿入位置--;
			}
			if (Input::key.Delete.on && 挿入位置 < (int)入力中文字.size())
			{
				入力中文字.erase(挿入位置, 1);
			}
			
			if (Input::key.Left.on || (Input::key.Left.holdCount > 30 && Input::key.Left.holdCount % 5 == 0))
			{
				挿入位置 = std::max(挿入位置 - 1, 0);
			}
			if (Input::key.Right.on || (Input::key.Right.holdCount > 30 && Input::key.Right.holdCount % 5 == 0))
			{
				挿入位置 = std::min(挿入位置 + 1, (int)入力中文字.size());
			}

		}

	};
}