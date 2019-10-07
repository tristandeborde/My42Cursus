#ifndef CSVREADER_CLASS_HPP
#define	CSVREADER_CLASS_HPP

#include <vector>
#include <iostream>

class CSVReader
{
	/* Instantiation **************************************************************/
	public:
		explicit CSVReader(std::string &filename);

	/* Methods ********************************************************************/
	public:
		std::vector<std::vector<std::string> > getData(bool header) const;

	/* Attributes *****************************************************************/
	private:
		std::string _file_name {};
		std::string _delimeter {","};

	/* Coplien methods ************************************************************/
	public:
		CSVReader(void)	 = default;
		~CSVReader(void) = default;
		CSVReader& operator=(const CSVReader&) = delete;
		CSVReader(const CSVReader&) = delete;
};

#endif	// #ifndef CSVREADER_CLASS_HPP
