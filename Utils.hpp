#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <vector>
#include <cctype>

#define RESET "\e[0m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define CYAN "\e[36m"
#define GRAY "\e[37m"


		// errors
#define ERR_NOSUCHSERVER 402 			//" :No such server\n"		
#define ERR_NOSUCHCHANNEL 403 			//":No such channel\n"		
#define ERR_NOMOTD 422 					//":MOTD File is missing"			
#define ERR_NONICKNAMEGIVEN 431			//":No nickname given\n"	
#define ERR_ERRONEUSNICKNAME 432 		//":Erroneus nickname\n"
#define ERR_NICKNAMEINUSE 433 			//":Nickname is already in use\n"	
#define ERR_NICKCOLLISION 436 			//"<nick> :Nickname collision KILL\n"
#define ERR_NOTONCHANNEL 442			//":You're not on that channel\n"	
#define ERR_NOTREGISTERED 451			//":You have not registered\n"		
#define ERR_NEEDMOREPARAMS 461			//":Not enough parameters\n"		
#define ERR_ALREADYREGISTRED 462		//":You may not reregister\n"	
#define ERR_PASSWDMISMATCH 464			//":Password incorrect\n"			
#define ERR_KEYSET 467					//":Channel key already set\n"				
#define ERR_UNKNOWNMODE 472				//":is unknown mode char to me\n"		
#define ERR_NOPRIVILEGES 481			//":Permission Denied- You're not an IRC operator"
#define ERR_CHANOPRIVSNEEDED 482		//":You're not channel operator\n"	
#define ERR_NOOPERHOST 491				//":No O-lines for your host\n"			
#define ERR_USERSDONTMATCH 502			//":Cant change mode for other users\n"

		// replies
#define RPL_ADMINME 256 		//" :Admin name - "													// 256
#define RPL_ADMINLOC1 257		//"Location - Kazan, Republic of Tatarstan, Russian Federation\n" 	// 257
#define RPL_ADMINEMAIL 259		//":Admin email - "												// 259
#define RPL_USERHOST 302		//":" [<reply>{<space><reply>}] <reply> ::= <nick>['*'] '=' <'+'|'-'><hostname>"
#define RPL_ISON 303			//":"													// 303
#define RPL_WHOISUSER 311		//"<nick> <user> <host> * :<real name>"								// 311
#define RPL_WHOISSERVER 312		//"<nick> <server> :<server info>" 								// 312
#define RPL_WHOISOPERATOR 313	//" :is an IRC operator\n"										// 313
#define RPL_WHOISIDLE 317		//" <integer> :seconds idle\n"										// 317
#define RPL_ENDOFWHOIS 318		//" :End of /WHOIS list\n"											// 318
#define RPL_LISTSTART 321		//"Channel :Users  Name\n"											// 321
#define RPL_LIST 322			//"<channel> <# visible> :<topic>"										// 322
#define RPL_NOTOPIC 331			//":No topic is set\n" 												// 331 
#define RPL_TOPIC 332			//"<channel> :<topic>\n"			 									// 332  
#define RPL_VERSION 351			//" :RFC 1459  | May 1993\n"											// 351
#define RPL_NAMREPLY 353		//"<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]" 					// 353
#define RPL_ENDOFNAMES 366		//":End of /NAMES list\n" 											// 366 
#define RPL_INFO 371			//":"																	// 371
#define RPL_MOTD 372			//":- "																	// 372
#define RPL_ENDOFINFO 374		//":End of /INFO list\n"											// 374
#define RPL_MOTDSTART 375		//" Message of the day - \n"										// 375
#define RPL_ENDOFMOTD 376		//":End of /MOTD command\n"											// 376
#define RPL_YOUREOPER 381		//":You are now an IRC operator\n"									// 381
#define RPL_REHASHING 382		//":Rehashing"														// 382
#define RPL_TIME 391			//" :Local time - "	

std::vector<std::string> split(std::string str, std::string delimiter);
bool    isAlphaStr(std::string str);
bool	isDigitStr(std::string str);
bool    contains( std::vector<std::string> vect, std::string str );
bool    contains( std::vector<User*> vect, User * user );
void	eraseString( std::vector<std::string> & vect, std::string name );
void    eraseUser( std::vector<User*> & vect, User * user );
int		checkWildcard(const char *str, const char *mask);

#endif