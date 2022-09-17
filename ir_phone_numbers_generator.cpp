#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

const unsigned int BATCH_SIZE = 1000000;
const unsigned int LINEAR_SEARCH_SIZE = BATCH_SIZE / 10000;
const std::string FILE_PATH = "all_phone_numbers.txt";
const std::string PREFIX = "09";
static std::vector<std::string> number_batch = {};


bool binary_search(const std::vector<std::string>& file_numbers, const std::string& element) {
	size_t low = 0;
	size_t hight = file_numbers.size() - 1;
	size_t mid = 0;

	// do a little linear search from begin and end of list
	for (size_t i = 0; i <= LINEAR_SEARCH_SIZE; i++) {
		if (i > hight) {
			break;
		}
		if (file_numbers[i] == element) {
			return true;
		}
	}
	for (size_t i = hight; i > hight - LINEAR_SEARCH_SIZE; i--) {
		if (file_numbers[i] == element) {
			return true;
		}
	}

	while (low <= hight)
	{
		mid = low + (hight - low) / 2;

		if (file_numbers[mid] < element) {
			low = mid + 1;
		}
		else if (file_numbers[mid] > element)
		{
			hight = mid - 1;
		}
		else {
			return true;
		}
	}
	return false;
}

inline bool is_number_exists_in_file(const std::vector<std::string>& file_numbers,const std::string& n) {
	if (file_numbers.empty()) {
		return false;
	}
	return binary_search(file_numbers,n);
}

inline bool is_file_exists(const std::string& path)
{
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

std::vector<std::string> read_file_numbers(std::ifstream& file)
{
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}
	return lines;
}
void append_number_to_file(std::ofstream& file, const std::string& number)
{
	file << number << "\n";
}

bool is_file_empty(std::ifstream& file)
{
	return file.peek() == std::fstream::traits_type::eof();
}

int main()
{
	std::cout << "The program will generate 1000000 numbers and then add them to file, and goes to generate next 1000000 numbers" << std::endl;

	const static std::string numbers[10] = { "0","1","2","3","4","5","6","7","8","9" };
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
											std::cout << "Adding " + std::to_string(BATCH_SIZE) + " of numbers to file" << std::endl;

											// open read file
											std::ifstream in_file{ FILE_PATH };
											if (!in_file.is_open())
											{
												std::cout << "We couldn't open/create file";
												exit(EXIT_FAILURE);
											}
											// check emptiness
											bool is_empty = is_file_empty(in_file);
											// if isn't empty read numbers from it
											std::vector<std::string> file_numbers;
											if (!is_empty)
											{
												file_numbers = read_file_numbers(in_file);
											}
											// close read file
											in_file.close();

											// open append file
											std::ofstream out_file {FILE_PATH,std::ios::app};
											if (!out_file.is_open())
											{
												std::cout << "We couldn't open/create file";
												exit(EXIT_FAILURE);
											}
											for (size_t i = 0; i <= BATCH_SIZE - 1; i++)
											{
												if (is_empty)
												{
													append_number_to_file(out_file,number_batch[i]);
													std::cout << number_batch[i] + " Added to "+ FILE_PATH << std::endl;
												}
												else{
													if (is_number_exists_in_file(file_numbers, number_batch[i]))
													{
														std::cout << number_batch[i] + " Is already added to " + FILE_PATH << std::endl;
													}
													else {
														append_number_to_file(out_file, number_batch[i]);
														std::cout << number_batch[i] + " Added to "+ FILE_PATH << std::endl;
													}
												}
											}
											number_batch.clear();
											out_file.close();
										}
										else {
											std::cout << std::to_string(batch_size) + " Number generated" << std::endl;
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
