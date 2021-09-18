#include <iostream>
#include <fstream>
#include <string>

#include "library.pb.h"

void show_book(const my_library::Book& book)
{
	std::cout <<
		"book: " << book.name() <<
		"\n\tisbn: " << book.isbn() <<
	"\n\tprice: " << book.price() <<
	"\n\tclassification: " << book.classification() <<
	"\n\tpublisher: name->" << book.publisher().name() << " location->" << book.publisher().location() <<
	"\n\tauthors: ";
	for(const auto& a : book.authors())
	{
		std::cout << a << '\t';
	}
	std::cout << std::endl;
}

void add_a_book(my_library::Book& book)
{
	std::cout << "input book name: \n";
	std::cin >> *book.mutable_name();

	std::cout << "input bool isbn: \n";
	std::cin >> *book.mutable_isbn();

	std::cout << "input book price: \n";
	double price;
	std::cin >> price;
	book.set_price(price);

	std::cout << "input book classification(valid classification: unknown, computer, science and social): \n";
	std::string classification;
	std::cin >> classification;
	if(classification == "computer")
	{
		book.set_classification(my_library::Book::Classification::Book_Classification_COMPUTER);
	}
	else if(classification == "science")
	{
		book.set_classification(my_library::Book::Classification::Book_Classification_SCIENCE);
	}
	else if(classification == "social")
	{
		book.set_classification(my_library::Book::Classification::Book_Classification_SOCIAL);
	}
	else
	{
		book.set_classification(my_library::Book::Classification::Book_Classification_UNKNOWN);
	}

	std::cout << "input publisher name and location: \n";
	auto* pub = book.mutable_publisher();
	std::cin >> *pub->mutable_name() >> *pub->mutable_location();

	std::cout << "input the number of authors of this book: \n";
	std::size_t num;
	std::cin >> num;
	for(; num != 0; --num)
	{
		std::cout << "input author name: \n";
		std::cin >> *book.add_authors();
	}
}

void show_library(const my_library::Library& library)
{
	std::cout <<
			"library " << library.name() <<
			"(location: " << library.location() <<
			") currently has " << library.books_size() <<
			" books in total.\n";
	for(const auto& b : library.books())
	{
		show_book(b);
	}
}

void create_new_library()
{
	my_library::Library library;

	std::cout << "create a new library, input library name and location: \n";
	std::cin >> *library.mutable_name() >> *library.mutable_location();

	std::cout << "Ready to add books, please input how many books to add: \n";
	std::size_t num;
	std::cin >> num;
	for(; num != 0; --num)
	{
		auto* book = library.add_books();
		add_a_book(*book);
	}

	show_library(library);

	std::cout << "input a dump file name: \n";
	std::string filename;
	std::cin >> filename;
	std::ofstream file{filename, std::ios::out | std::ios::binary};
	if(!file)
	{
		std::cerr << "cannot open file " << filename << ", maybe you don't have permission!\n";
	}

	if(!library.SerializeToOstream(&file))
	{
		std::cerr << "dump file " << filename << " failed!\n";
	}
	else
	{
		std::cout << "dump file " << filename << " succeeded!\n";
	}
	file.close();
}

int main(int argc, char* argv[])
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if(argc != 2)
	{
		std::cerr << "Usage:  " << argv[0] << " PATH_TO_LIBRARY_DATA_FILE\n";
		std::cerr << "Or do you need to create one?(type `yes` to create one): \n";

		std::string create;
		std::cin >> create;
		if(create == "yes")
		{
			create_new_library();
		}
		else
		{
			return -1;
		}
	}
	else
	{
		my_library::Library library;

		// read the existing library
		std::fstream input(argv[1], std::ios::in | std::ios::binary);
		if(!input)
		{
			std::cerr << "file " << argv[1] << " cannot open, maybe you don't have permission or it not exist!\n";
			return -1;
		}
		else if(!library.ParseFromIstream(&input))
		{
			std::cerr << "failed to parse library file " << argv[1] << "\n";
			return -1;
		}

		show_library(library);
	}

	// Optional:  Delete all global objects allocated by protobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
