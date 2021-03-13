//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

#include <SDXFramework.h>
#include <Multimedia/SDXafx.h>
#include <Tiled/TmxToGUI.h>

SDX::ImagePack imageS;
SDX::IFrame* frameS[10];
SDX::IFont* fontS[10];

#include "TestScene.h"

bool SampleTiled()
{
	using namespace SDX;
	//事前にtemplate.tmxをコードに変換し
	//TestScene等のコードを作成しておく事
	System::Initialise("test", 640, 480);

	imageS.LoadTmx("template.tmx");
	fontS[0] = new Font(SystemFont::Gothic, 10);
	auto frame0 = ImagePack("data/pipo-WindowBase001.png", 9, 3, 3);
	auto frame1 = ImagePack("data/pipo-WindowBase004.png", 9, 3, 3);
	frameS[0] = new BmpFrame(&frame0);
	frameS[1] = new BmpFrame(&frame1);

	TestScene scene;

	while (System::Update())
	{
		scene.Draw();
	}

	return true;
}