// Test.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// detect memory leak 
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
#include <crtdbg.h>
//#include <stdio.h>

#include <future>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

#include "Itemfactory_test.h"


//@ async and mutex
#include "GotoBed.h"
#include "Future_exception.h"

#include "Test_RandomImageFloat.h"	//@ create random image
#include "Test_Thresholdings.h"		//@ serial test
#include "Test_Documents.h"			//@ test document and stream
#include "Test_Instances.h"			//@ test for memory release and removing
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

static void Mat_array_vector_compare()
{
	int width = 10000;
	int height = 10000;

	auto start = std::chrono::high_resolution_clock::now();
	float** mat_array = new float*[width];
	for (int i = 0; i < height; ++i)
	{
		mat_array[i] = new float[height];
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> sec = end - start;
	std::cout << "creation of 2'd float array : " << sec.count() << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			float value = mat_array[y][x];
		}
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "access of 2'd float array : " << sec.count() << std::endl;

	start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<float>> mat_vector;
	mat_vector.resize(height);
	for (int i = 0; i < height; ++i)
	{
		mat_vector[i].resize(height);
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "creation of 2'd float vector : " << sec.count() << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (auto row : mat_vector)
	{
		for (auto v : row)
		{
			float value = v;
		}
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "access of 2'd float vector : " << sec.count() << std::endl;

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::cout << "Hello World!\n";

	//Items::ItemFactory_Test();

	// test for go to bed example
	//Beds::GoToBedsAsync();

	// serial and multi-threading test
	//serial_document_compare();

	//Test::Documents::Test_FreeDocument();
	//Test::Documents::Test_FreeItem();
	//Test::Documents::Test_FreePropertyGroup();
	//Test::Documents::Test_FreePropertyBase();
	//Test::Documents::Test_FreeIComputable();
	//Test::Documents::Test_FreeImageComputable();

	//Test::Items::ItemFactory_Item_List();

	//Test::Instances::Test_FreeItemsInDocument();
	AsyncException::GoToBedAsync_Exception();

	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(2239);
	
}
