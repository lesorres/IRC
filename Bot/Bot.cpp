#include "Bot.hpp"

Bot::Bot() {
	cmd.insert(std::make_pair("/HELP", &Bot::help));
	cmd.insert(std::make_pair("/PASS", &Bot::pass));
	cmd.insert(std::make_pair("/NICK", &Bot::nick));
	cmd.insert(std::make_pair("/USER", &Bot::user));
	cmd.insert(std::make_pair("/OPER", &Bot::oper));
	cmd.insert(std::make_pair("/QUIT", &Bot::quit));
	cmd.insert(std::make_pair("/JOIN", &Bot::join));
	cmd.insert(std::make_pair("/PART", &Bot::part));
	cmd.insert(std::make_pair("/MODE", &Bot::mode));
	cmd.insert(std::make_pair("/TOPIC", &Bot::topic));
	cmd.insert(std::make_pair("/NAMES", &Bot::names));
	cmd.insert(std::make_pair("/LIST", &Bot::list));
	cmd.insert(std::make_pair("/INVITE", &Bot::invite));
	cmd.insert(std::make_pair("/KICK", &Bot::kick));
	cmd.insert(std::make_pair("/VERSION", &Bot::version));
	cmd.insert(std::make_pair("/TIME", &Bot::time));
	cmd.insert(std::make_pair("/ADMIN", &Bot::admin));
	cmd.insert(std::make_pair("/INFO", &Bot::info));
	cmd.insert(std::make_pair("/PRIVMSG", &Bot::privmsg));
	cmd.insert(std::make_pair("/NOTICE", &Bot::notice));
	cmd.insert(std::make_pair("/WHO", &Bot::who));
	cmd.insert(std::make_pair("/WHOIS", &Bot::whois));
	cmd.insert(std::make_pair("/WHOWAS", &Bot::whowas));
	cmd.insert(std::make_pair("/KILL", &Bot::kill));
	cmd.insert(std::make_pair("/PING", &Bot::ping));
	cmd.insert(std::make_pair("/PONG", &Bot::pong));
	cmd.insert(std::make_pair("/AWAY", &Bot::away));
	cmd.insert(std::make_pair("/REHASH", &Bot::rehash));
	cmd.insert(std::make_pair("/RESTART", &Bot::restart));
	cmd.insert(std::make_pair("/USERHOST", &Bot::userhost));
	cmd.insert(std::make_pair("/ISON", &Bot::ison));
	cmd.insert(std::make_pair("/COMMAND", &Bot::command));
}

void Bot::run() {
	while (1) {
		std::cin >> cmds;
		execute();
	}
}

void Bot::execute() {
	try    {
    	(this->*(cmd.at(cmds)))();
	}
	catch(const std::exception& e)		{
		std::cerr << e.what() << '\n';
	}
	cmds.clear();
}

Bot::~Bot() {
}

int Bot::help() {
	std::cout << CYAN << "\n   You need to register to start working on the server.\n\
You need to complete the mandatory commands - " << RESET << "\e[1mPASS\e[0m, \n\
\e[1mNICK\e[0m " << CYAN << "and " << RESET << "\e[1mUSER\e[0m. " << CYAN << "You cann't starrt working in the server\n\
until these commands are executed. Call one of the\n\
commands " << PURPLE << "/PASS, /NICK" << CYAN << " or " << PURPLE << "/USER" << CYAN << " to learn how to execute\n\
these commands.\n   If you want to see a lost of all commands enter " << PURPLE << "/COMMAND\n\n"  RESET;
	return 0;
}

int Bot::command() {
	std::cout << "\nList of all IRC commands:\n\n" << YELLOW << "1. Connection Registration:\n" <<
	CYAN <<	"- /PASS;\n- /NICK;\n- /USER;\n- /OPER;\n- /QUIT;\n\n" << YELLOW << "2. Channel operations:\n" <<
	CYAN << "- /JOIN;\n- /PART;\n- /MODE;\n- /TOPIC;\n- /NAMES;\n- /LIST;\n- /INVITE;\n- /KICK;\n\n" <<
	YELLOW << "3. Server queries and commands:\n" << CYAN << "- /VERSION;\n- /TIME;\n- /ADMIN;\n- /INFO;\n\n" <<
	YELLOW << "4. Sending messages:\n" << CYAN << "- /PRIVMSG;\n- /NOTICE;\n\n" << YELLOW <<
	"5. User based queries:\n" << CYAN << "- /WHO;\n- /WHOIS;\n- /WHOWAS;\n\n" << YELLOW << 
	"6. Miscellaneous messages:\n" << CYAN << "- /KILL;\n- /PING;\n- /PONG;\n\n" << YELLOW <<
	 "7. Optionals:\n" << CYAN << "- /AWAY;\n- /REHASH;\n- /RESTART;\n- /USERHOST;\n- /ISON.\n" << RESET;
	return 0;
}

int Bot::pass(){
	std::cout << "\n      Command: \e[1mPASS\e[0m\n   Parameters: <password>\n\n" << CYAN <<
"The " << RESET << "PASS " << CYAN << "command is used to set a 'connection password'.The\n\
optional password can and MUST be set before any attempt to register the\n\
connection is made.  Currently this requires that user send a " << RESET << "PASS " << CYAN << "command\n\
before sending the " << RESET << "NICK/USER " << CYAN << "combination.\n" << RESET;
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mPASS\e[0m " << RESET << "secretpasswordhere\n\n";
	return 0;
}

int Bot::nick(){
	std::cout << "\n      Command: \e[1mNICK\e[0m\n   Parameters: <nickname>\n\n\e[1mNICK\e[0m " << CYAN <<
"message is used to give user a nickname or change the previous one.\n\
If a " << RESET << "\e[1mNICK\e[0m " << CYAN << "message arrives at a server which already knows about\n\
an identical nickname for another client, a nickname collision occurs.\n" << RESET;
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mNICK\e[0m " << RESET << "Wiz\n" << GREEN << ":WiZ \e[1mNICK\e[0m " << RESET << "Kilroy\n\n";
	return 0;
}

int Bot::user(){
	std::cout << "\n      Command: \e[1mUSER\e[0m\n   Parameters: <username> <hostname> <servername> <realname>\n\n"\
	<< CYAN << "The " << RESET << "\e[1mUSER\e[0m" << CYAN << " message is used at the beginning of connection to specify\n\
the username, hostname, servername and realname of s new user.  It is\n\
also used in communication between servers to indicate new user\n\
arriving on IRC, since only after both " << RESET << "\e[1mUSER\e[0m" << CYAN << " and " << RESET << "\e[1mNICK\e[0m" << CYAN << " have been\n\
received from a client does a user become registered.\n\
It must be noted that realname parameter must be the last parameter,\n\
because it may contain space characters and must be prefixed with a\n\
colon (':') to make sure this is recognised as such.\n" << RESET;
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mUSER\e[0m " << RESET << "guest tolmoon tolsun :Ronnie Reagan\n\n";
	return 0;
}

int Bot::oper(){
	std::cout << "\n      Command: \e[1mOPER\e[0m\n   Parameters: <user> <password>\n\n"\
	"\e[1mOPER\e[0m " << CYAN << "message is used by a normal user to obtain operator privileges.\n\
The combination of <user> and <password> are required to gain Operator privileges.\n\
If the client sending the OPER command supplies the correct password\n\
for the given user, the server then informs the rest of the network\n\
of the new operator by issuing a \"" << RESET << "\e[1mMODE +o\e[0m" << CYAN << "\" for the clients nickname.\n";
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mOPER\e[0m " << RESET << "foo bar\n\n";
	return 0;
}

int Bot::quit(){
	std::cout << "\n      Command: \e[1mQUIT\e[0m\n   Parameters: [<Quit message>]\n\n" << CYAN <<
"A client session is ended with a quit message.  The server must close\n\
the connection to a client which sends a " << RESET << "\e[1mQUIT\e[0m" << CYAN << " message. If a \"Quit \n\
Message\" is given, this will be sent instead of the default message,\n\
the nickname.";
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mQUIT\e[0m " << RESET << ":Gone to have lunch\n\n";
	return 0;
}

int Bot::join(){
	std::cout << "\n      Command: \e[1mJOIN\e[0m\n   Parameters: <channel>{,<channel>} [<key>{,<key>}]\n\n" << CYAN <<
   "The " << RESET << "\e[1mJOIN\e[0m\n " << CYAN << "command is used by client to start listening a specific\n\
channel. Whether or not a client is allowed to join a channel is\n\
checked only by the server the client is connected to; all other\n\
servers automatically add the user to the channel when it is received\n\
from other servers.  The conditions which affect this are as follows:\n\
   1. the user must be invited if the channel is invite-only;\n\
   2. the user's nick/username/hostname must not match any active bans;\n\
   3. the correct key (password) must be given if it is set.\n\
These are discussed in more detail under the " << RESET << "\e[1mMODE\e[0m " << CYAN << "command\n\
Once a user has joined a channel, they receive notice about all\n\
commands their server receives which affect the channel.  This\n\
includes " << RESET << "\e[1mMODE\e[0m, \e[1mKICK\e[0m, \e[1mPART\e[0m, \e[1mQUIT\e[0m" << CYAN << 
" and of course " << RESET << "\e[1mPRIVMSG/NOTICE\e[0m" << CYAN << ". The\n" << RESET << "\e[1mJOIN\e[0m" << CYAN <<
" command needs to be broadcast to all servers so that each server\n\
knows where to find the users who are on the channel.  This allows\n\
optimal delivery of " << RESET << "\e[1mPRIVMSG/NOTICE\e[0m" << CYAN << " messages to the channel.\n\
If a " << RESET << "\e[1mJOIN\e[0m " << CYAN << "is successful, the user is then sent the channel's topic\n\
and the list of users who are on the channel, which must include the user joining.\n\
";
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mJOIN\e[0m " << RESET << "#foobar\n\n" << 
GREEN << "\e[1mJOIN\e[0m " << RESET << "#foo fubar\n\n" << GREEN << "\e[1mJOIN\e[0m " <<
RESET << "#foo,#bar\n\n:WiZ " <<  GREEN << "\e[1mJOIN\e[0m " << RESET << "#Twilight_zone\n\n";
	return 0;
}

int Bot::part(){
	std::cout << "\n      Command: \e[1mPART\e[0m\n   Parameters: <channel>{,<channel>}\n\n" << CYAN <<
	"The " << RESET << "\e[1mPART\e[0m" << CYAN << " message causes the client sending the message to be removed\n\
from the list of active users for all given channels listed in the\n\
parameter string.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mPART\e[0m " << RESET << "#twilight_zone\n\n" 
	<< GREEN << "\e[1mPART\e[0m " << RESET << "#oz-ops, #group5\n\n";
	return 0;
}

int Bot::mode(){
	std::cout << "\n      Command: \e[1mMODE\e[0m\n\n" << CYAN << "The " << RESET << "\e[1mMODE\e[0m" << CYAN << 
" command is a dual-purpose command in IRC.  It allows both\n\
usernames and channels to have their mode changed.\n";
std::cout << "\n      Channel modes\nParameters: <channel> {[+|-]|o|p|s|i|t|n|b|v}[<limit>][<user>][<ban mask>]\n\n" <<
CYAN << "The " << RESET << "\e[1mMODE\e[0m" << CYAN << " command is provided so that channel operators may change the\n\
characteristics of `their' channel.  It is also required that servers\n\
be able to change channel modes so that channel operators may be created.\n\n\
The various modes available for channels are as follows:\n\n" <<
RESET << " \e[1mo\e[0m" << CYAN << " - give/take channel operator privileges;\n"
RESET << " \e[1mp\e[0m" << CYAN << " - private channel flag;\n"
RESET << " \e[1ms\e[0m" << CYAN << " - secret channel flag;\n"
RESET << " \e[1mi\e[0m" << CYAN << " - invite-only channel flag;\n"
RESET << " \e[1mt\e[0m" << CYAN << " - topic settable by channel operator only flag;\n"
RESET << " \e[1mn\e[0m" << CYAN << " - no messages to channel from clients on the outside;\n"
RESET << " \e[1mm\e[0m" << CYAN << " - moderated channel;\n"
RESET << " \e[1ml\e[0m" << CYAN << " - set the user limit to channel;\n"
RESET << " \e[1mb\e[0m" << CYAN << " - set a ban mask to keep users out;\n"
RESET << " \e[1mv\e[0m" << CYAN << " - give/take the ability to speak on a moderated channel;\n"
RESET << " \e[1mk\e[0m" << CYAN << " - set a channel key (password).\n";
   std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mMODE\e[0m " << RESET << "#Finnish +im\n\n" << 
GREEN << "\e[1mMODE\e[0m " << RESET << "#Finnish +o Kilroy\n\n" << GREEN << "\e[1mMODE\e[0m " << RESET << "#Finnish +v Wiz\n\n" <<
GREEN << "\e[1mMODE\e[0m " << RESET << "#eu-opers +l 10\n\n";
std::cout << "\n      User modes\nParameters: <nickname> {[+|-]|i|w|s|o}\n\n" <<
CYAN << "The user " << RESET << "\e[1mMODE\e[0m" << CYAN << "s are typically changes which affect either how the\n\
client is seen by others or what 'extra' messages the client is sent.\n\
A user " << RESET << "\e[1mMODE\e[0m" << CYAN << " command may only be accepted if both the sender of the\n\
message and the nickname given as a parameter are both the same.\n\n\
The available modes are as follows:\n\n" << 
RESET << " \e[1mi\e[0m" << CYAN << " - marks a users as invisible;\n"
RESET << " \e[1ms\e[0m" << CYAN << " - marks a user for receipt of server notices;\n"
RESET << " \e[1mw\e[0m" << CYAN << " - user receives wallops;\n"
RESET << " \e[1mo\e[0m" << CYAN << " - operator flag.\n";
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1m:MODE\e[0m " << RESET << "WiZ -w\n\n:Angel " << 
GREEN << "\e[1mMODE\e[0m " << RESET << "Angel +i\n\n" << GREEN << "\e[1mMODE\e[0m " << RESET << "WiZ -o\n\n";
	return 0;
}

int Bot::topic(){
	std::cout << "\n      Command: \e[1mTOPIC\e[0m\n   Parameters: <channel> [<topic>]\n\n" << CYAN <<
	"The " << RESET << "\e[1mTOPIC\e[0m" << CYAN << " message is used to change or view the topic of a channel.\n\
The topic for channel <channel> is returned if there is no <topic>\n\
given.  If the <topic> parameter is present, the topic for that\n\
channel will be changed, if the channel modes permit this action.\n";
	std::cout << PURPLE << "\nExample:\n" << RESET << ":Wiz " << GREEN << "\e[1mTOPIC\e[0m " << RESET << "#test :New topic\n\n" 
	<< GREEN << "\e[1mTOPIC\e[0m " << RESET << "#test :another topic\n\n" << GREEN << "\e[1mTOPIC\e[0m " << RESET << "#test\n\n";
	return 0;
}

int Bot::names(){
	std::cout << "\n      Command: \e[1mNAMES\e[0m\n   Parameters: [<channel>{,<channel>}]\n\n" << CYAN <<
"By using the " << RESET << "\e[1mNAMES\e[0m" << CYAN << " command, a user can list all nicknames that are\n\
visible to them on any channel that they can see. Channel names\n\
which they can see are those which aren't private (+p) or secret (+s)\n\
or those which they are actually on.\n\nIf no <channel> parameter is given, a list of all channels and their\n\
occupants is returned.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mNAMES\e[0m " << RESET << "#twilight_zone,#42\n\n" 
	<< GREEN << "\e[1mNAMES\e[0m\n\n" << RESET;
	return 0;
}

int Bot::list(){
	std::cout << "\n      Command: \e[1mLIST\e[0m\n   Parameters: [<channel>{,<channel>} [<server>]]\n\n" << CYAN 
<< "Lists all channels on the server. If the comma-separated list\n\
<channels> is given, it will return the channel topics. If <server>\n\
is given, the command will be forwarded to <server> for evaluation. \n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mLIST\e[0m " << RESET << "#twilight_zone,#42\n\n" 
	<< GREEN << "\e[1mLIST\e[0m\n\n" << RESET;
	return 0;
}

int Bot::invite(){
	std::cout << "\n      Command: \e[1mINVITE\e[0m\n   Parameters: <nickname> <channel>\n\n" << CYAN 
<< "Invites <nickname> to the channel <channel>. <channel> does not have\n\
to exist, but if it does, only members of the channel are allowed\n\
to invite other clients. If the channel mode i is set, only channel\n\
operators may invite other clients.\n";
	std::cout << PURPLE << "\nExample:\n" << RESET << ":Angel " << GREEN << "\e[1mINVITE\e[0m " << RESET << "Wiz #Dust \n\n" 
	<< GREEN << "\e[1mINVITE\e[0m" << RESET << "Wiz #Twilight_Zone\n\n";
	return 0;
}

int Bot::kick(){
	std::cout << "\n      Command: \e[1mKICK\e[0m\n   Parameters: <channel> <user> [<comment>]\n\n" << CYAN 
<< "Forcibly removes <client> from <channel>. This command may only be issued by channel operators.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mKICK\e[0m" << RESET << " #Finnish John :Speaking English\n\n" <<
	RESET << ":WiZ " << GREEN << "\e[1mKICK\e[0m " << RESET << "#Finnish John\n\n";
	return 0;
}

int Bot::version(){
	std::cout << "\n      Command: \e[1mVERSION\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
<< "Returns the version of <server>, or the current server if omitted.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mVERSION\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mVERSION\e[0m\n\n" << RESET;
	return 0;
}

int Bot::time(){
	std::cout << "\n      Command: \e[1mTIME\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
	<< "Returns the local time on the current server, or <server> if specified.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mTIME\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mTIME\e[0m\n\n" << RESET;
	return 0;
}

int Bot::admin(){
	std::cout << "\n      Command: \e[1mADMIN\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
	<< "The admin message is used to find the name of the administrator of\n\
the given server, or current server if <server> parameter is omitted.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mADMIN\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mADMIN\e[0m\n\n" << RESET;
	return 0;
}

int Bot::info(){
	std::cout << "\n      Command: \e[1mINFO\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
	<< "The " << RESET << "\e[1mINFO\e[0m" << CYAN << " command is required to return information which describes\n\
the server: its version, when it was compiled, the patchlevel, when\n\
it was started\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mINFO\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mINFO\e[0m\n\n" << RESET;
	return 0;
}

int Bot::privmsg(){
	std::cout << "\n      Command: \e[1mPRIVMSG\e[0m\n   Parameters: <receiver>{,<receiver>} <text to be sent>\n\n" << CYAN 
	<< "Sends <text to be sent> to <receiver>, which is usually a user or channel.\n";
	std::cout << PURPLE << "\nExample:\n" << RESET << ":Angel " << GREEN << "\e[1mPRIVMSG\e[0m" << RESET << "Wiz :Hello are you receiving this message ?\n\n" <<
	GREEN << "\e[1mPRIVMSG\e[0m" << RESET << " Angel :yes I'm receiving it !receiving it !'u>(768u+1n)\n\n" << 
	GREEN << "\e[1mPRIVMSG\e[0m" << RESET << " jto@tolsun.oulu.fi :Hello !\n\n" <<
	GREEN << "\e[1mPRIVMSG\e[0m" << RESET << " #*.edu :NSFNet is undergoing work, expect interruptions\n\n";
	return 0;
}

int Bot::notice(){
	std::cout << "\n      Command: \e[1mNOTICE\e[0m\n   Parameters: <nickname> <text>\n\n" << CYAN
	<< "This command works similarly to " << RESET << "\e[1mPRIVMSG\e[0m" << CYAN << ", except automatic replies\n\
must never be sent in reply to " << RESET << "\e[1mNOTICE\e[0m" << CYAN << " messages.\n";
	return 0;
}

int Bot::who(){
	std::cout << "\n      Command: \e[1mWHO\e[0m\n   Parameters: [<name> [<o>]]\n\n" << CYAN
	<< "Returns a list of users who match <name>. If the flag \"o\" is\n\
given, the server will only return information about IRC operators.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mWHO\e[0m" << RESET << " *.fi\n\n" <<
	GREEN << "\e[1mWHO\e[0m" << RESET << " jto* o\n\n";
	return 0;
}

int Bot::whois(){
	std::cout << "\n      Command: \e[1mWHOIS\e[0m\n   Parameters: <nickmask>[,<nickmask>[,...]]\n\n" << CYAN
	<< "Returns information about the comma-separated list of nicknames masks\n\
<nicknames>.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mWHOIS\e[0m" << RESET << " wiz\n\n";
	return 0;
}

int Bot::whowas(){
	std::cout << "\n      Command: \e[1mWHOWAS\e[0m\n   Parameters: <nickname> [<count>]\n\n" << CYAN
	<< "Used to return information about a nickname that is no longer in\n\
use (due to client disconnection, or nickname changes).";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mWHOWAS\e[0m" << RESET << " Wiz\n\n";
	return 0;
}
int Bot::kill(){
	std::cout << "\n      Command: \e[1mKILL\e[0m\n   Parameters: <nickname> <comment>\n\n" << CYAN
	<< "";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mKILL\e[0m" << RESET << " David\n\n";
	return 0;
}
int Bot::ping(){
	return 0;
}
int Bot::pong(){
	return 0;
}
int Bot::away(){
	return 0;
}
int Bot::rehash(){
	return 0;
}
int Bot::restart(){
	return 0;
}
int Bot::userhost(){
	return 0;
}
int Bot::ison(){
	return 0;
}

void Bot::showInfo() {
	std::cout << CYAN << "\n	Welcome to Chat Bot!\n\
This bot is made to help you work with IRC: \n\
the bot shows you what commands are implemented\n\
and what arguments must be entered in order for\n\
the server to understand and correctly process\n\
your request.\n\
We aren't to code a client and this IRC don't  handle\n\
server to server communication.\n\
If you want to see the list of commands supported\n\
in this IRC enter " << PURPLE << "/HELP.\n\n" << RESET;
}

int main()	{
	Bot bot;
	std::string cin;
	while (cin != "/START") {
		std::cout << "Enter '/START' to start working\n";
		std::cin >> cin;
	}
	bot.showInfo();
	bot.run();
	std::cout << cin << std::endl;
}