#include "Bot.hpp"

void Bot::execute() {
	try    {
    	(this->*(commands.at(cmds)))();
	}
	catch(const std::exception& e)		{
		std::cerr << e.what() << '\n';
	}
	cmds.clear();
}

void Bot::initMap() {
	commands.insert(std::make_pair("/HELP", &Bot::help));
	commands.insert(std::make_pair("/PASS", &Bot::passCmd));
	commands.insert(std::make_pair("/NICK", &Bot::nickCmd));
	commands.insert(std::make_pair("/USER", &Bot::userCmd));
	commands.insert(std::make_pair("/OPER", &Bot::operCmd));
	commands.insert(std::make_pair("/QUIT", &Bot::quitCmd));
	commands.insert(std::make_pair("/JOIN", &Bot::joinCmd));
	commands.insert(std::make_pair("/PART", &Bot::partCmd));
	commands.insert(std::make_pair("/MODE", &Bot::modeCmd));
	commands.insert(std::make_pair("/TOPIC", &Bot::topicCmd));
	commands.insert(std::make_pair("/NAMES", &Bot::namesCmd));
	commands.insert(std::make_pair("/LIST", &Bot::listCmd));
	commands.insert(std::make_pair("/INVITE", &Bot::inviteCmd));
	commands.insert(std::make_pair("/KICK", &Bot::kickCmd));
	commands.insert(std::make_pair("/VERSION", &Bot::versionCmd));
	commands.insert(std::make_pair("/TIME", &Bot::timeCmd));
	commands.insert(std::make_pair("/ADMIN", &Bot::adminCmd));
	commands.insert(std::make_pair("/INFO", &Bot::infoCmd));
	commands.insert(std::make_pair("/PRIVMSG", &Bot::privmsgCmd));
	commands.insert(std::make_pair("/NOTICE", &Bot::noticeCmd));
	commands.insert(std::make_pair("/WHO", &Bot::whoCmd));
	commands.insert(std::make_pair("/WHOIS", &Bot::whoisCmd));
	commands.insert(std::make_pair("/WHOWAS", &Bot::whowasCmd));
	commands.insert(std::make_pair("/KILL", &Bot::killCmd));
	commands.insert(std::make_pair("/PING", &Bot::pingCmd));
	commands.insert(std::make_pair("/PONG", &Bot::pongCmd));
	commands.insert(std::make_pair("/AWAY", &Bot::awayCmd));
	commands.insert(std::make_pair("/REHASH", &Bot::rehashCmd));
	commands.insert(std::make_pair("/RESTART", &Bot::restartCmd));
	commands.insert(std::make_pair("/USERHOST", &Bot::userhostCmd));
	commands.insert(std::make_pair("/ISON", &Bot::isonCmd));
	commands.insert(std::make_pair("/COMMAND", &Bot::command));
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

int Bot::passCmd(){
	std::cout << "\n      Command: \e[1mPASS\e[0m\n   Parameters: <password>\n\n" << CYAN <<
"The " << RESET << "PASS " << CYAN << "command is used to set a 'connection password'.The\n\
optional password can and MUST be set before any attempt to register the\n\
connection is made.  Currently this requires that user send a " << RESET << "PASS " << CYAN << "command\n\
before sending the " << RESET << "NICK/USER " << CYAN << "combination.\n" << RESET;
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mPASS\e[0m " << RESET << "secretpasswordhere\n\n";
	return 0;
}

int Bot::nickCmd(){
	std::cout << "\n      Command: \e[1mNICK\e[0m\n   Parameters: <nickname>\n\n\e[1mNICK\e[0m " << CYAN <<
"message is used to give user a nickname or change the previous one.\n\
If a " << RESET << "\e[1mNICK\e[0m " << CYAN << "message arrives at a server which already knows about\n\
an identical nickname for another client, a nickname collision occurs.\n" << RESET;
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mNICK\e[0m " << RESET << "Wiz\n" << GREEN << ":WiZ \e[1mNICK\e[0m " << RESET << "Kilroy\n\n";
	return 0;
}

int Bot::userCmd() {
	std::cout << "\n      Command: \e[1mUSER\e[0m\n   Parameters: <username> <hostname> <servername> <realname>\n\n"\
	<< CYAN << "This command is used at the beginning of a connection to specify the\n\
username, hostname, real name and initial user modes of the\n\
connecting client. <realname> may contain spaces, and thus\n\
must be prefixed with a colon.\n" << RESET;
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mUSER\e[0m " << RESET << "guest tolmoon tolsun :Ronnie Reagan\n\n";
	return 0;
}

int Bot::operCmd() {
	std::cout << "\n      Command: \e[1mOPER\e[0m\n   Parameters: <user> <password>\n\n"\
	"\e[1mOPER\e[0m " << CYAN << "authenticates a user as an IRC operator on that server/network.\n";
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mOPER\e[0m " << RESET << "foo bar\n\n";
	return 0;
}

int Bot::quitCmd() {
	std::cout << "\n      Command: \e[1mQUIT\e[0m\n   Parameters: [<Quit message>]\n\n" << CYAN <<
"A client session is ended with a quit message.  The server must close\n\
the connection to a client which sends a " << RESET << "\e[1mQUIT\e[0m" << CYAN << " message. If a \"Quit \n\
Message\" is given, this will be sent instead of the default message,\n\
the nickname.";
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mQUIT\e[0m " << RESET << ":Gone to have lunch\n\n";
	return 0;
}

int Bot::joinCmd() {
	std::cout << "\n      Command: \e[1mJOIN\e[0m\n   Parameters: <channel>{,<channel>} [<key>{,<key>}]\n\n" << CYAN <<
   "Makes the client join the channels in the comma-separated list\n\
<channels>, specifying the passwords, if needed, in the comma-separated\n\
list <keys>. If the channel(s) do not exist then they will be created.\n";
std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mJOIN\e[0m " << RESET << "#foobar\n\n" << 
GREEN << "\e[1mJOIN\e[0m " << RESET << "#foo fubar\n\n" << GREEN << "\e[1mJOIN\e[0m " <<
RESET << "#foo,#bar\n\n:WiZ " <<  GREEN << "\e[1mJOIN\e[0m " << RESET << "#Twilight_zone\n\n";
	return 0;
}

int Bot::partCmd() {
	std::cout << "\n      Command: \e[1mPART\e[0m\n   Parameters: <channel>{,<channel>}\n\n" << CYAN <<
	"The " << RESET << "\e[1mPART\e[0m" << CYAN << " message causes the client sending the message to be removed\n\
from the list of active users for all given channels listed in the\n\
parameter string.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mPART\e[0m " << RESET << "#twilight_zone\n\n" 
	<< GREEN << "\e[1mPART\e[0m " << RESET << "#oz-ops, #group5\n\n";
	return 0;
}

int Bot::modeCmd() {
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

int Bot::topicCmd() {
	std::cout << "\n      Command: \e[1mTOPIC\e[0m\n   Parameters: <channel> [<topic>]\n\n" << CYAN <<
	"The " << RESET << "\e[1mTOPIC\e[0m" << CYAN << " message is used to change or view the topic of a channel.\n\
The topic for channel <channel> is returned if there is no <topic>\n\
given.  If the <topic> parameter is present, the topic for that\n\
channel will be changed, if the channel modes permit this action.\n";
	std::cout << PURPLE << "\nExample:\n" << RESET << ":Wiz " << GREEN << "\e[1mTOPIC\e[0m " << RESET << "#test :New topic\n\n" 
	<< GREEN << "\e[1mTOPIC\e[0m " << RESET << "#test :another topic\n\n" << GREEN << "\e[1mTOPIC\e[0m " << RESET << "#test\n\n";
	return 0;
}

int Bot::namesCmd() {
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

int Bot::listCmd() {
	std::cout << "\n      Command: \e[1mLIST\e[0m\n   Parameters: [<channel>{,<channel>} [<server>]]\n\n" <<
	CYAN << "Lists all channels on the server. If the comma-separated list\n\
<channels> is given, it will return the channel topics. If <server>\n\
is given, the command will be forwarded to <server> for evaluation. \n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mLIST\e[0m " << RESET << "#twilight_zone,#42\n\n" 
	<< GREEN << "\e[1mLIST\e[0m\n\n" << RESET;
	return 0;
}

int Bot::inviteCmd() {
	std::cout << "\n      Command: \e[1mINVITE\e[0m\n   Parameters: <nickname> <channel>\n\n" 
	<< CYAN << "Invites <nickname> to the channel <channel>. <channel> does not have\n\
to exist, but if it does, only members of the channel are allowed\n\
to invite other clients. If the channel mode i is set, only channel\n\
operators may invite other clients.\n";
	std::cout << PURPLE << "\nExample:\n" << RESET << ":Angel " << GREEN
	<< "\e[1mINVITE\e[0m " << RESET << "Wiz #Dust \n\n" 
	<< GREEN << "\e[1mINVITE\e[0m" << RESET << "Wiz #Twilight_Zone\n\n";
	return 0;
}

int Bot::kickCmd() {
	std::cout << "\n      Command: \e[1mKICK\e[0m\n   Parameters: <channel> <user> [<comment>]\n\n" << CYAN 
<< "Forcibly removes <client> from <channel>. This command may only be issued by channel operators.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mKICK\e[0m" << RESET << " #Finnish John :Speaking English\n\n" <<
	RESET << ":WiZ " << GREEN << "\e[1mKICK\e[0m " << RESET << "#Finnish John\n\n";
	return 0;
}

int Bot::versionCmd() {
	std::cout << "\n      Command: \e[1mVERSION\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
<< "Returns the version of <server>, or the current server if omitted.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mVERSION\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mVERSION\e[0m\n\n" << RESET;
	return 0;
}

int Bot::timeCmd() {
	std::cout << "\n      Command: \e[1mTIME\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
	<< "Returns the local time on the current server, or <server> if specified.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mTIME\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mTIME\e[0m\n\n" << RESET;
	return 0;
}

int Bot::adminCmd(){
	std::cout << "\n      Command: \e[1mADMIN\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
	<< "The admin message is used to find the name of the administrator of\n\
the given server, or current server if <server> parameter is omitted.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mADMIN\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mADMIN\e[0m\n\n" << RESET;
	return 0;
}

int Bot::infoCmd(){
	std::cout << "\n      Command: \e[1mINFO\e[0m\n   Parameters: [<server>]\n\n" << CYAN 
	<< "The " << RESET << "\e[1mINFO\e[0m" << CYAN << " command is required to return information which describes\n\
the server: its version, when it was compiled, the patchlevel, when\n\
it was started\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mINFO\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mINFO\e[0m\n\n" << RESET;
	return 0;
}

int Bot::privmsgCmd(){
	std::cout << "\n      Command: \e[1mPRIVMSG\e[0m\n   Parameters: <receiver>{,<receiver>} <text to be sent>\n\n" << CYAN 
	<< "Sends <text to be sent> to <receiver>, which is usually a user or channel.\n";
	std::cout << PURPLE << "\nExample:\n" << RESET << ":Angel " << GREEN << "\e[1mPRIVMSG\e[0m" 
	<< RESET << "Wiz :Hello are you receiving this message ?\n\n" <<
	GREEN << "\e[1mPRIVMSG\e[0m" << RESET << " Angel :yes I'm receiving it !receiving it !'u>(768u+1n)\n\n" << 
	GREEN << "\e[1mPRIVMSG\e[0m" << RESET << " jto@tolsun.oulu.fi :Hello !\n\n" <<
	GREEN << "\e[1mPRIVMSG\e[0m" << RESET << " #*.edu :NSFNet is undergoing work, expect interruptions\n\n";
	return 0;
}

int Bot::noticeCmd(){
	std::cout << "\n      Command: \e[1mNOTICE\e[0m\n   Parameters: <nickname> <text>\n\n" << CYAN
	<< "This command works similarly to " << RESET << "\e[1mPRIVMSG\e[0m" << CYAN << ", except automatic replies\n\
must never be sent in reply to " << RESET << "\e[1mNOTICE\e[0m" << CYAN << " messages.\n\n" << RESET;
	return 0;
}

int Bot::whoCmd(){
	std::cout << "\n      Command: \e[1mWHO\e[0m\n   Parameters: [<name> [<o>]]\n\n" << CYAN
	<< "Returns a list of users who match <name>. If the flag \"o\" is\n\
given, the server will only return information about IRC operators.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mWHO\e[0m" << RESET << " *.fi\n\n" <<
	GREEN << "\e[1mWHO\e[0m" << RESET << " jto* o\n\n";
	return 0;
}

int Bot::whoisCmd(){
	std::cout << "\n      Command: \e[1mWHOIS\e[0m\n   Parameters: <nickmask>[,<nickmask>[,...]]\n\n" << CYAN
	<< "Returns information about the comma-separated list of nicknames masks\n\
<nicknames>.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mWHOIS\e[0m" << RESET << " wiz\n\n";
	return 0;
}

int Bot::whowasCmd(){
	std::cout << "\n      Command: \e[1mWHOWAS\e[0m\n   Parameters: <nickname> [<count>]\n\n" << CYAN
	<< "Used to return information about a nickname that is no longer in\n\
use (due to client disconnection, or nickname changes).\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mWHOWAS\e[0m" << RESET << " Wiz\n\n";
	return 0;
}

int Bot::killCmd(){
	std::cout << "\n      Command: \e[1mKILL\e[0m\n   Parameters: <nickname> <comment>\n\n" << CYAN
	<< "Forcibly removes <nickname> from the network. This command\n\
may only be issued by IRC operators.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mKILL\e[0m" << RESET << " David\n\n";
	return 0;
}

int Bot::pingCmd(){
	std::cout << "\n      Command: \e[1mPING\e[0m\n   Parameters: <server1>\n\n" << CYAN
	<< "Tests the presence of a connection. A " << RESET << "\e[1mPING\e[0m" 
	<< CYAN << " message results\nin a " << RESET << "\e[1mPONG\e[0m" << CYAN << " reply.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mPING\e[0m" << RESET << " IRC.1\n\n" <<
	GREEN << "\e[1mPING\e[0m" << RESET << " WiZ\n\n";
	return 0;
}

int Bot::pongCmd(){
	std::cout << "\n      Command: \e[1mPONG\e[0m\n   Parameters: <daemon> [<daemon2>]\n\n" << CYAN
	<< "This command is a reply to the " << RESET << "\e[1mPING\e[0m" << CYAN <<
	" command and works in much the same way.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mPONG\e[0m" << RESET << " IRC.1\n\n";
	return 0;
}

int Bot::awayCmd(){
	std::cout << "\n      Command: \e[1mAWAY\e[0m\n   Parameters: [message]\n\n" << CYAN
	<< "Provides the server with a message to automatically send in reply\n\
to a " << RESET << "\e[1mPRIVMSG\e[0m" << CYAN << " directed at the user, but \
not to a channel they are on.\n\
If <message> is omitted, the away status is removed.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mAWAY\e[0m" << RESET <<
	" :Gone to lunch\n\n:WiZ " << GREEN << "\e[1mAWAY\e[0m\n\n";
	return 0;
}

int Bot::rehashCmd(){
	std::cout << "\n      Command: \e[1mREHASH\e[0m\n   Parameters: None\n\n" << CYAN
	<< "Causes the server to re-read and re-process its configuration\n\
file(s). This command can only be sent by IRC operators.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mREHASH\e[0m\n\n" << RESET;
	return 0;
}

int Bot::restartCmd(){
	std::cout << "\n      Command: \e[1mRESTART\e[0m\n   Parameters: None\n\n" << CYAN
	<< "The restart message can only be used by an operator to force a server\n\
restart itself. This message is optional since it may be viewed as a\n\
risk to allow arbitrary people to connect to a server as an operator\n\
and execute this command, causing (at least) a disruption to service.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mRESTART\e[0m\n\n" << RESET;
	return 0;
}

int Bot::userhostCmd(){
	std::cout << "\n      Command: \e[1mUSERHOST\e[0m\n   Parameters: \
<nickname>{<space><nickname>}\n\n" << CYAN
	<< "The " << RESET << "\e[1mUSERHOST\e[0m" << CYAN << " command takes a list of up to 5 nicknames, each\n\
separated by a space character and returns a list of information\n\
about the nicknames specified.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mUSERHOST\e[0m" 
	<< RESET << " Wiz Michael Marty p\n\n";
	return 0;
}

int Bot::isonCmd(){
	std::cout << "\n      Command: \e[1mISON\e[0m\n   Parameters: \
<nickname>{<space><nickname>}\n\n" << CYAN
	<< "Queries the server to see if the clients in the space-separated\n\
list <nicknames> are currently on the network. The server returns\n\
only the nicknames that are on the network in a space-separated\n\
list. If none of the clients are on the network the server returns\n\
an empty list.\n";
	std::cout << PURPLE << "\nExample:\n" << GREEN << "\e[1mISON\e[0m" 
	<< RESET << " phone trillian WiZ jarlek Avalon Angel Monstah\n\n";
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