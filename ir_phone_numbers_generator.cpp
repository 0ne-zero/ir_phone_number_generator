#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

const unsigned int BATCH_SIZE = 10000000;
const unsigned int WAIT_TIME = 3;
const std::string FILE_PATH = "all_phone_numbers.txt";
const std::string PREFIX = "09";
static std::vector<std::string> number_batch = {};

inline bool is_file_exists(const std::string &path)
{
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}
void append_number_to_file(std::ofstream &file, const std::string &number)
{
	file << number << "\n";
}
std::string read_last_line_of_file(std::ifstream &file)
{
	if (file.is_open())
	{
		file.seekg(-3, std::ios_base::end);
		bool keepLooping = true;
		while (keepLooping)
		{
			char ch;
			file.get(ch);
			if ((int)file.tellg() <= 1)
			{
				file.seekg(0);
				keepLooping = false;
			}
			else if (ch == '\n')
			{
				keepLooping = false;
			}
			else
			{
				file.seekg(-2, std::ios_base::cur);
			}
		}
		std::string lastLine;
		std::getline(file, lastLine);
		return lastLine;
	}
	return "";
}
bool is_file_empty(std::ifstream &file)
{
	return file.peek() == std::fstream::traits_type::eof();
}
long long read_last_number_of_file()
{
	if (is_file_exists(FILE_PATH))
	{
		// open file for read
		std::ifstream in_file{FILE_PATH};
		if (!in_file.is_open())
		{
			std::cout << "We couldn't open/create file";
			exit(EXIT_FAILURE);
		}
		// check emptiness
		bool is_empty = is_file_empty(in_file);
		// if isn't empty read numbers from it
		if (!is_empty)
		{
			std::string last_number = read_last_line_of_file(in_file);
			if (!last_number.empty())
			{
				long long last_number_int = std::stoll(last_number, nullptr, 10);
				return last_number_int;
			}
			return 0;
		}
		// close read file
		return 0;
	}
	return 0;
}

int main()
{
	std::cout << "The program will generate 1000000 numbers and then add them to file, and goes to generate next 1000000 numbers" << std::endl;
	int counter = 0;
	/* wait for WAIT_TIME seconds */
	while (true)
	{
		if (counter == WAIT_TIME)
		{
			break;
		}
		else
		{
			std::cout << "\rThe program will start in " << WAIT_TIME - counter << " seconds" << std::flush;
			sleep(1);
			counter++;
		}
	}
	std::cout << "\33[2K" << std::flush;
	const static std::string numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	for (std::string a : numbers)
	{
		for (std::string b : numbers)
		{
			for (std::string c : numbers)
			{
				for (std::string d : numbers)
				{
					for (std::string e : numbers)
					{
						for (std::string f : numbers)
						{
							for (std::string g : numbers)
							{
								for (std::string h : numbers)
								{
									for (std::string i : numbers)
									{
										const std::string nine_numbers = a + b + c + d + e + f + g + h + i;
										const std::string complete_number = PREFIX + nine_numbers;
										number_batch.push_back(complete_number);
 										const size_t batch_size = number_batch.size();
										if (batch_size == BATCH_SIZE)
										{
											// get last number in file
											long long last_number = read_last_number_of_file();
											if (std::stoll(number_batch[number_batch.size() - 1]) <= last_number)
											{
												std::cout << "The created batch fo number already exists in " + FILE_PATH << " file" << std::endl;
												std::cout << "The program is creating the next batch of numbers" << std::endl;
											}
											else
											{
												std::cout << "Writing the batch of numbers to " << FILE_PATH << " file" << std::endl;
												// open append file
												std::ofstream out_file{FILE_PATH, std::ios::app};
												if (!out_file.is_open())
												{
													std::cout << "The program couldn't open/create file";
													exit(EXIT_FAILURE);
												}
												for (size_t i = 0; i <= BATCH_SIZE - 1; i++)
												{
													if (last_number != 0)
													{
														if (std::stoll(number_batch[i]) <= last_number)
														{
															std::cout << number_batch[i] + " already exists in " + FILE_PATH << " file" << std::endl;
														}
														else
														{
															append_number_to_file(out_file, number_batch[i]);
															std::cout << number_batch[i] + " Added to " + FILE_PATH << " file" << std::endl;
														}
													}
													else
													{
														append_number_to_file(out_file, number_batch[i]);
														std::cout << number_batch[i] + " Added to " + FILE_PATH << " file" << std::endl;
													}
												}
												out_file.close();
											}
											number_batch.clear();
										}
										else
										{
											std::cout << complete_number + " Added to batch of numbers" << std::endl;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
