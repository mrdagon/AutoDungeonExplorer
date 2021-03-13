//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//[サンプルコード作成中]
bool SampleDirector()
{
	using namespace SDX;
	class SceneA : public IScene
	{
	public:

		Image back;

		SceneA()
		{
			back.Make(640, 480);
		}

		~SceneA()
		{


		}

		void Update() override
		{

			if (Input::key.A.on)
			{
				Director::ActiveScene(1);
			}

			if (Input::key.Return.on)
			{
				Director::GetScene(0)->isEnd = true;
				Director::GetScene(1)->isEnd = true;
			}
		}
		void Draw() override
		{

			Screen::SetTarget(&back);
			double x = Rand::Get(640.0);
			double y = Rand::Get(480.0);
			Color color = { Rand::Get(255), Rand::Get(255), Rand::Get(255) };
			Drawing::Circle({ x, y, 30 }, color);
			Screen::SetTarget();

			back.Draw({0,0});

			Drawing::String({ 10, 10 }, Color::White, "現在のSceneはA\nAキーでScene切り替え、Returnで終了");
		}
	};

	class SceneB : public IScene
	{
	public:

		int time = 0;

		SceneB()
		{

		}

		~SceneB()
		{

		}

		void Update() override
		{
			++time;
			if (time > 640){ time = 0; }

			if (Input::key.A.on)
			{
				Director::ActiveScene(1);
			}

			if (Input::key.Return.on)
			{ 
				Director::GetScene(0)->isEnd = true;
				Director::GetScene(1)->isEnd = true;
			}
		}
		void Draw() override
		{
			Drawing::String({ 10, 10 }, Color::White, "現在のSceneはB\nAキーでScene切り替え、Returnで終了");

			Drawing::Rect({ 0, 100, time, 280 }, Color::White);
		}
	};

	using namespace SDX;
	System::Initialise("sample", 640, 480);

	//shared_ptrの関係でAとBでデストラクタを呼ばれるタイミングが変わる
	std::shared_ptr<SceneA> sceneA = std::make_shared<SceneA>();

	Director::AddScene(sceneA);
	Director::AddScene(std::make_shared<SceneB>());

	Director::Run();

	System::End();
	return true;
}