#pragma once

#include <future>
#include <algorithm>
#include <numeric>

namespace AsyncException
{
	static std::mutex bed_mutex;

	static bool GoToBed_exception_async(std::string name, int time)
	{
		// await semaphore or mutex
		printf("%s wait lock\n", name);
		//std::cout << name << " wait lock" << std::endl;
		std::lock_guard<std::mutex> lock(bed_mutex);	// lock_guard automatically release lock
		{
			printf("%s got lock\n", name);
			//std::cout << name << " got lock" << std::endl;
			
			// goto bed
			printf("%s go to bed and sleep during %d\n", name, time);
			//std::cout << name << " go to bed and sleep during " << time << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(time));

			// occur error when time is even.
			if (time % 2 == 0)
			{
				std::string error = name + " error in go to bed";
				printf(error.c_str());
				throw std::exception(error.c_str());
			}

			// awake
			printf("%s wake up\n", name);
			//std::cout << name << " wake up" << std::endl;
		}
		printf("%s release lock\n", name);
		//std::cout << name << " release lock" << std::endl;

		return true;
	}

	static void GoToBedAsync_Exception()
	{
		srand((unsigned int)time(0));	// random seed
		std::vector<std::pair<std::string, int>> name_and_times;

		for (int i = 0; i < 5; i++)
		{
			std::string name(1, static_cast<char>(97 + i));
			int time = rand() % 1000;
			name_and_times.push_back(std::pair<std::string, int>(name, time));
		}

		// set future to 'GoToBed' with asynchronos task
		std::vector<std::future<bool>> futures;
		for (auto pair : name_and_times)
		{
			try
			{
				std::future<bool> future = std::async(std::launch::async,
					GoToBed_exception_async, pair.first, pair.second);
				futures.push_back(std::move(future));
				
			}
			catch (const std::exception& e)
			{
				std::string error = "error in future " + std::string(e.what());
				printf(error.c_str());
			}
		}

		std::vector<bool> ress;
		for (int i = 0; i < 5; i++)
		{
			std::future<bool> &future = futures.at(i);
			try
			{
				bool valid = future.valid();
				bool res = future.get();
				ress.push_back(res);
			}
			catch (const std::exception& e)
			{
				std::string a = e.what();
				std::cout << "[error] " << e.what() << std::endl;
			}
			
		}


	}
}
