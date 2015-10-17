#include "AgendaUI.h"
#include "AgendaService.h"
#include <iomanip>
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::setiosflags;

void upboundary() {
  cout << "------------------------------";
  cout << " Agenda ";
  cout << "------------------------------";
  cout << endl;
}
void lowboundary() {
  cout << "------------------------------";
  cout << "--------";
  cout << "------------------------------";
  cout << endl;
}
void help() {
  upboundary();
  cout << "Action :" << endl
       << "o   - log out Agenda" << endl
       << "dc  - delete Agenda account" << endl
       << "lu  - list all Agenda account" << endl
       << "cm  - create a meeting" << endl
       << "la  - list all meetings" << endl
       << "las - list all sponsor meetings" << endl
       << "lap - list all participate meetings" << endl
       << "qm  - query meeting by title" << endl
       << "qt  - query meeting by time interval" << endl
       << "dm  - delete meeting by title" << endl
       << "da  - dalete all meetings" << endl
       << "h   - help" << endl;
       lowboundary();
}

  //  "dfkja dfakj dfaj"  return dfkja
std::string cut(int & start, const std::string & input) {
  if (start >= input.size()) return "";
  int end = start, len = input.size();
  for (end = start; end < len; end++) {
    if (input[end] == ' ') break;
  }
  std::string result = input.substr(start, end - start);
  start = end + 1;
  return result;
}

  // public
AgendaUI::AgendaUI(): agendaService_() {}

void AgendaUI::OperationLoop(void) {
  while (1) {
    startAgenda();
    cout << endl << "Agenda : ~$ ";
    std::string input = getOperation();
    int start = 0;
    std::string operate = cut(start, input);
    if (operate == "l") userLogIn();
    if (operate == "r") userRegister();
    if (operate == "q") {
      quitAgenda();
      break;
    }
  }
}


  // private;
void AgendaUI::startAgenda(void) {
  upboundary();
  cout << "Action :" << endl;
  cout << "l  - log in Agenda by user name and password" << endl;
  cout << "r  - register an Agenda accout" << endl;
  cout << "q  - quit Agenda" << endl;
  lowboundary();
}

std::string AgendaUI::getOperation() {
  std::string input;
  getline(std::cin, input);
  return input;
}

bool AgendaUI::executeOperation(std::string op) {}

void AgendaUI::userLogIn(void) {
  cout << "[log in] [user name] [password]" << endl;
  cout << "[log in] ";

  std::string input = getOperation();
  int start = 0;
  userName_ = cut(start, input);
  userPassword_ = cut(start, input);
  if (userName_.empty()||userPassword_.empty()) {
    cout << "[error] log in fail!" << endl;
    return;
  }
  if (agendaService_.userLogIn(userName_, userPassword_)) {
    help();
    cout << "[log in] succeed!" << endl;

    while (1) {
      cout << endl << "Agenda@" << userName_ << " : # ";
      std::string operate = getOperation();
      if (operate == "o") {
        userLogOut();
       break;
      }
      if (operate == "dc") {
        deleteUser();  //  point may be bug
        break;
      }
      if (operate == "lu") listAllUsers();
      if (operate == "cm") createMeeting();
      if (operate == "la") listAllMeetings();
      if (operate == "las") listAllSponsorMeetings();
      if (operate == "lap") listAllParticipateMeetings();
      if (operate == "qm") queryMeetingByTitle();
      if (operate == "qt") queryMeetingByTimeInterval();
      if (operate == "dm") deleteMeetingByTitle();
      if (operate == "da") deleteAllMeetings();
    }
  } else {
    cout << "[error] log in fail!" << endl;
  }
}

void AgendaUI::userRegister(void) {
  cout << "[register] [user name] [password] [email] [phone]" << endl;
  cout << "[register] ";
  string name, password, email, phone;
  string input = getOperation();
  int start = 0;
  name = cut(start, input);
  password = cut(start, input);
  email = cut(start, input);
  phone = cut(start, input);
  //  cin >> name >> password >> email >> phone;
  if (name.empty()||password.empty()) {
    cout << "[error] register fail!" << endl;
    return;
  }
  if (agendaService_.userRegister(name, password, email, phone)) {
    cout << "[register] succeed!" << endl;
  } else {
    cout << "[error] register fail!" << endl;
  }
}

void AgendaUI::quitAgenda(void) {
  agendaService_.quitAgenda();
}

void AgendaUI::userLogOut(void) {
  agendaService_.quitAgenda();
}

void AgendaUI::deleteUser(void) {
  if (agendaService_.deleteUser(userName_, userPassword_)) {
    cout << "[delete agenda account] succeed!" << endl;
  } else {
    //  should can't use it
    cout << "[error] delete agenda account fail!" << endl;
  }
}

void AgendaUI::listAllUsers(void) {
  std::list<User> result = agendaService_.listAllUsers();
  cout << setiosflags(std::ios::left);
  // cout << "name\temail\tphone\n" << endl;
  cout << setw(15) << "name" << setw(20) << "email" << setw(15) << "phone"
       << endl;
  std::list<User>::iterator it, end;
  for (it = result.begin(), end = result.end(); it != end; it++) {
    cout << setw(15) << it->getName() << setw(20) << it->getEmail() << setw(15)
         << it->getPhone() << endl;
  }
}

void AgendaUI::createMeeting(void) {
  cout << "[create meeting] [title] [participator] ";
  cout << "[start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]";
  cout << endl;
  cout << "[create meeting] ";
  string title, participator, startDate, endDate;
  string input = getOperation();
  int start = 0;
  title = cut(start, input);
  participator = cut(start, input);
  startDate = cut(start, input);
  endDate = cut(start, input);
  if (title.empty()||participator.empty()||startDate.empty()||
      endDate.empty()) {
    cout << "[error] create meeting fail!" << endl;
    return;
  }
  if (agendaService_.createMeeting(userName_, title, participator,
      startDate, endDate)) {
    cout << "[create meeting] succeed!" << endl;
  } else {
    cout << "[error] create meeting fail!" << endl;
  }
}

void AgendaUI::listAllMeetings(void) {
  cout << "[list all meetings]\n" << endl;
  printMeetings(agendaService_.listAllMeetings(userName_));
}

void AgendaUI::listAllSponsorMeetings(void) {
  cout << "[list all sponsor meetings]\n" << endl;
  printMeetings(agendaService_.listAllSponsorMeetings(userName_));
}

void AgendaUI::listAllParticipateMeetings(void) {
  cout << "[list all participator meetings]\n" << endl;
  printMeetings(agendaService_.listAllParticipateMeetings(userName_));
}

void AgendaUI::queryMeetingByTitle(void) {
  cout << "[query meeting] [title]:" << endl;
  cout << "[query meeting] ";
  string title;
  title = getOperation();
  //  cin >> title;
  std::list<Meeting> result = agendaService_.meetingQuery(userName_, title);
  cout << setiosflags(std::ios::left);
  cout << "sponsor\tparticipator\t"
       << setw(20) << "start time" << setw(20) << "end time" << endl;
  std::list<Meeting>::iterator it, end;
  for (it = result.begin(), end= result.end(); it != end; it++) {
    cout << it->getSponsor() << "\t" << setw(16) << it->getParticipator()
         << setw(20) << Date::dateToString(it->getStartDate())
         << setw(20) << Date::dateToString(it->getEndDate()) << endl;
  }
}

void AgendaUI::queryMeetingByTimeInterval(void) {
  cout << "[query meetings] [start time<yyyy-mm-dd/hh:mm>] [end time"
       << "<yyyy-mm-dd/hh:mm>]" << endl;
  cout << "[query meetings] ";
  string startDate, endDate, input;
  //  cin >> startDate >> endDate;
  input = getOperation();
  int start = 0;
  startDate = cut(start, input);
  endDate = cut(start, input);
  std::list<Meeting> result = agendaService_.meetingQuery(userName_,
    startDate, endDate);
  cout << "[query meetings]" << endl;
  cout << setiosflags(std::ios::left);
  cout << "title\tsponsor\tparticipator\t"
       << setw(20) << "start time" << setw(20) << "end time" << endl;
  std::list<Meeting>::iterator it, end;
  for (it = result.begin(), end = result.end(); it != end; it++) {
    cout << it->getTitle() << "\t" << it->getSponsor() << "\t"
         << it->getParticipator() << "\t"
         << setw(20) << Date::dateToString(it->getStartDate())
         << setw(20) << Date::dateToString(it->getEndDate()) << endl;
  }
}

void AgendaUI::deleteMeetingByTitle(void) {
  cout << "[delete meeting] [title]" << endl;
  cout << "[delete meeting] ";
  string title;
  title = getOperation();
  //  cin >> title;
  if (agendaService_.deleteMeeting(userName_, title)) {
    cout << "\n[delete meeting by title] succeed!" << endl;
  } else {
    cout << "\n[error] delete meeting fail!" << endl;
  }
}

void AgendaUI::deleteAllMeetings(void) {
  if (agendaService_.deleteAllMeetings(userName_)) {
    cout << "\n[delete all meetings] succeed!" << endl;
  } else {
    // should not use it
    cout << "\n[error] delete all meetings fail!" << endl;
  }
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  cout << setiosflags(std::ios::left);
  cout << "title\tsponsor\tparticipator\t"
       << setw(20) << "start time" << "end time\n";
  std::list<Meeting>::iterator it, end;
  for (it = meetings.begin(), end = meetings.end(); it != end; it++) {
    //  cout << setiosflags(std::ios::left);
    cout << it->getTitle() << "\t" << it->getSponsor() << "\t"
         << setw(16) << it->getParticipator()
         << setw(20) << Date::dateToString(it->getStartDate())
         << setw(20) << Date::dateToString(it->getEndDate()) << endl;
  }
}

