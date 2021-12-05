// #include <iostream>
// #include "Command.hpp"

// int main ()
// {
// 	std::string str = ":prexif commmmmmand param1 para2 par3  o    :trtr   tr   tr";
// 	Command someCommand;

// 	someCommand.parseMsg(str);

// 	std::vector<std::string>::iterator itBegin = someCommand.msg.midParams.begin();
// 	std::vector<std::string>::iterator itEnd = someCommand.msg.midParams.end();

// 	std::cout << "from main:\n";
// 	std::cout << "prefx  : |" << someCommand.msg.prefx << "|\n";
// 	std::cout << "command: |" << someCommand.msg.cmd << "|\n";
// 	std::cout << "mid params:\n";
// 	while (itBegin != itEnd)
// 	{
// 		std::cout << *itBegin << "\n";
// 		itBegin++;
// 	}
// 	std::cout << "postfix: |" << someCommand.msg.trailing << "|\n";
	
// 	return (0);
// }

// // "    :prexif commmmmmand param1 para2         nn"