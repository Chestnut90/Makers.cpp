// Test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// detect memory leak 
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
#include <crtdbg.h>
//#include <stdio.h>

#include <iostream>

#include "Itemfactory_test.h"


//@ async and mutex
#include "GotoBed.h"

#include "Test_RandomImageFloat.h"	//@ create random image
#include "Test_Thresholdings.h"		//@ serial test
#include "Test_Documents.h"			//@ test document and stream

void serial_document_compare()
{
	// create image
	long width, height;
	width = height = 5120;
	auto image = Test::RandomImageFloats::CreateRandomFloatArray(width, height, true);
	//std::cout << "\nserial thresholding without buffers" << std::endl;
	//Test::Thresholdings::ThresholdingWithoutBuffers(image, true);

	std::cout << "\nserial thresholding with buffers" << std::endl;
	Test::Thresholdings::ThresholdingWithBuffers(image, true);

	std::cout << "\ndocument with multi threading" << std::endl;
	Test::Documents::Run_Test(image, width, height);
	delete image;
}

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::cout << "Hello World!\n";

	//Items::ItemFactory_Test();

	// test for go to bed example
	//Beds::GoToBedsAsync();

	// serial and multi-threading test
	serial_document_compare();

	//Test::Documents::Test_FreeDocument();
	//Test::Documents::Test_FreeItem();
	//Test::Documents::Test_FreePropertyGroup();
	//Test::Documents::Test_FreePropertyBase();
	//Test::Documents::Test_FreeIComputable();
	//Test::Documents::Test_FreeImageComputable();

	Test::Items::ItemFactory_Item_List();

	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(2239);
	
}
