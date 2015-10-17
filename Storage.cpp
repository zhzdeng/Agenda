#include "Storage.h"
#include <iostream>
#include <fstream>

#define point_ instance_
// www.cnblogs.com/hujian/archive/2012/12/07/2807605.html

// I didn't use this point
// I used local static object;
// you should delete point by yourself
Storage* Storage::instance_ = NULL;
Storage::Storage(): userList_(), meetingList_() {}


//   deng  ->   "deng"     dfa,dfa"dad -> "dfa,dfa""dad"
std::string StringToCsv(const std::string & input) {
  std::string result;
  result += '"';
  int i = 0, end = input.size();
  for (i = 0; i < end; i++) {
    if (input[i] == '"') result += '"';
    result += input[i];
  }
  result += '"';
  return result;
}
  //   "deng" -> deng   "dfa,daf""dad" -> dfa,daf"dad
  //  delete "
std::string CsvToString(const std::string & input) {
  std::string result;
  int len = input.size();
  for (int i = 1; i < len - 1; i++) {
    if (input[i] == '"') {
      result += '"';
      i++;
    } else {
      result += input[i];
    }
  }
  return result;
}
std::string Cut(int &start, const std::string &input) {
  /****************************************************/
  // a line to single string                          //
  // "deng","bbb","11@qq.com","110" ->    "deng"      //
  //                                      "bbb"       //
  //                                      "11@qq.com" //
  //                                      "110"       //
  /****************************************************/
  //  cut   " is even and input[i] = ',';
  int count = 0, end = start;
  while (1) {
    if (count % 2 == 0&&(end >= input.size()||input[end] == ','))
      break;
    if (input[end] == '"') count++;
    end++;
  }
  std::string result = input.substr(start, end - start);
  start = end + 1;
  return result;
}
bool Storage::readFromFile(const char *fpath) {
  //  read user;
  std::string temp(fpath);
  // if (temp[temp.size() - 1] != '/') temp += '/';
  std::string user(temp);
  std::string input;
  user += "User.csv";
  std::ifstream userFile;
  userFile.open(user.c_str());
  if (!userFile) {
    /*/
    std::cout << "readFromFile fail" << std::endl;
    //*/
    return false;
  }
  getline(userFile, input);
  // read "\"name\",\"password\",\"email\",\"phone\"\n"

  /****************************************************/
  // Cut function                                     //
  /****************************************************/
  // a line to single string                          //
  // "deng","bbb","11@qq.com","110" ->    "deng"      //
  //                                      "bbb"       //
  //                                      "11@qq.com" //
  //                                      "110"       //
  /****************************************************/
  while (getline(userFile, input)) {
    if (input.size() < 2) break;
    int start = 0;
    std::string name = CsvToString(Cut(start, input));
    std::string password = CsvToString(Cut(start, input));
    std::string email = CsvToString(Cut(start, input));
    std::string phone = CsvToString(Cut(start, input));
    User temp(name, password, email, phone);
    //  std::cout << "here" << std::endl;
    //  if (instance_ == NULL) {
    //    std::cout << "isNull" << std::endl;
    //  }
    (instance_->userList_).push_back(temp);
    //  std::cout << "here" << std::endl;
  }
  userFile.close();

  //  read meeting
  std::string meeting = fpath;
  meeting += "Meeting.csv";
  std::ifstream meetingFile;
  meetingFile.open(meeting.c_str());
  if (!meetingFile) return false;
  getline(meetingFile, input);
  // read "\"sponsor\",\"participator\",\"sdate\",\"edate\",\"title\"";
  while (getline(meetingFile, input)) {
    if (input.size() < 2) break;
    int start = 0;
    std::string sponsor = CsvToString(Cut(start, input));
    std::string participator = CsvToString(Cut(start, input));
    std::string sdate = CsvToString(Cut(start, input));
    std::string edate = CsvToString(Cut(start, input));
    std::string title = CsvToString(Cut(start, input));
    point_->meetingList_.push_back(Meeting(sponsor, participator,
     Date::stringToDate(sdate), Date::stringToDate(edate), title));
  }
  meetingFile.close();
  return true;
}

bool Storage::writeToFile(const char *fpath) {
  // write user
  std::string temp(fpath);
  // fpath may be  ~/Desktop  ~/Desktop/
  // if (temp[temp.size() - 1] != '/') temp += '/';
  std::string user(temp);
  user += "User.csv";
  std::ofstream userFile;
  userFile.open(user.c_str());
  if (!userFile) {
  /*/
    std::cout << "writeToFile faile" << std::endl;
  //*/
    return false;
  }
  userFile << "\"name\",\"password\",\"email\",\"phone\"\n";
  for (std::list<User>::iterator it = point_->userList_.begin(),
    end = point_->userList_.end();
      it != end; it++) {
      userFile << StringToCsv(it->getName() ) << ',';
      userFile << StringToCsv(it->getPassword() ) << ',';
      userFile << StringToCsv(it->getEmail() ) << ',';
      userFile << StringToCsv(it->getPhone() ) << '\n';
  }
  userFile.close();

  // write meeting
  std::string meeting = fpath;
  meeting += "Meeting.csv";
  std::ofstream meetingFile;
  meetingFile.open(meeting.c_str());
  if (!meetingFile) return false;
  meetingFile <<
  "\"sponsor\",\"participator\",\"sdate\",\"edate\",\"title\"\n";
  for (std::list<Meeting>::iterator it = point_->meetingList_.begin(),
    end = point_->meetingList_.end();
      it != end; it++) {
      meetingFile << StringToCsv(it->getSponsor()) << ',';
      meetingFile << StringToCsv(it->getParticipator()) << ',';
      meetingFile << StringToCsv(Date::dateToString(
            it->getStartDate())) << ',';
      meetingFile << StringToCsv(Date::dateToString(
              it->getEndDate())) << ',';
      meetingFile << StringToCsv(it->getTitle()) << '\n';
  }
  meetingFile.close();
  return true;
}
  // static founciton
  /**********************************************/
  /*  the singleton way is  Local static object */
  /*     LOCAL STATIC OBJECT                    */
  /*                                            */
  /*  createUser createMeeting only ceart       */
  /*  queryUser queryMeeting delete and count   */
  /*  updateUser updateMeeting sent some data   */
  /*      and count                             */
  /*  deleteUser  deleteMeeting only delete     */
  /*                                            */
  /*                                            */
  /*                                            */
  /**********************************************/
  // change  in call function delete

Storage* Storage::getInstance(void) {
  // local static object
  if (instance_ == NULL) instance_ = new Storage();
  instance_->readFromFile("");
  return instance_;
}

Storage::~Storage() {
  instance_ = NULL;
}

    // CRUD for User & Meeting
    // using C++11 Function Template and Lambda Expressions
void Storage::createUser(const User& user) {
  point_->userList_.push_back(user);
}

std::list<User> Storage::queryUser(
            std::function<bool(const User&)> filter) {
  std::list<User> result;
  for (std::list<User>::iterator it = point_->userList_.begin(),
    end = point_->userList_.end(); it != end; it++) {
    if (filter(*it))  result.push_back(*it);
  }
  return result;
}
  //  return found users

int Storage::updateUser(std::function<bool(const User&)> filter,
        std::function<void(User&)> switcher) {
  int count = 0;
  for (std::list<User>::iterator it = point_->userList_.begin(),
       end = point_->userList_.end(); it != end; it++) {
    if (filter(*it)) {
      count++;
      switcher(*it);
    }
  }
  return count;
}
  //  return the number of updated users

int Storage::deleteUser(std::function<bool(const User&)> filter) {
  // delete and reutrn number
  int count = 0;
  for (std::list<User>::iterator it = point_->userList_.begin(),
    end = point_->userList_.end();
    it != end;) {
    if (filter(*it)) {
      count++;
      it = point_->userList_.erase(it);
    } else {
      it++;
    }
  }
  return count;
}
  //  return the number of deleted users

void Storage::createMeeting(const Meeting& meeting) {
  // only creat and not check some meet
  point_->meetingList_.push_back(meeting);
}

std::list<Meeting> Storage::queryMeeting(
                       std::function<bool(const Meeting&)> filter) {
  std::list<Meeting> result;
  for (std::list<Meeting>::iterator it = point_->meetingList_.begin(),
       end = point_->meetingList_.end(); it != end; it++) {
    if (filter(*it))  result.push_back(*it);
  }
  return result;
}
  //  return found meetings

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
        std::function<void(Meeting&)> switcher) {
  int count = 0;
  for (std::list<Meeting>::iterator it = point_->meetingList_.begin(),
       end = point_->meetingList_.end(); it != end; it++) {
    if (filter(*it)) {
      count++;
      switcher(*it);
    }
  }
  return count;
}
    //  return the number of updated meetings

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
  //  delete and reutrn number
  int count = 0;
  for (std::list<Meeting>::iterator it = point_->meetingList_.begin(),
    end = point_->meetingList_.end();
    it != end;) {
    if (filter(*it)) {
      count++;
      it = point_->meetingList_.erase(it);
    } else {
      it++;
    }
  }
  return count;
}
    //  return the number of deleted meetings

    //  File IO
bool Storage::sync(void) {
  return writeToFile("");
}

