#include "AgendaService.h"
#include <functional>
AgendaService::AgendaService() {
  startAgenda();
}

AgendaService::~AgendaService() {
  quitAgenda();
  delete storage_;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
  std::list<User> result = storage_->queryUser([&](const User & user)->bool{
    if (userName == user.getName()&&password == user.getPassword()) {
      return true;
    } else {
      return false;
    }
  });    //  lamda function

  if (result.size() == 1) {
    return true;
  } else {
    return false;
  }
}

  //  first queryUser
  //  second  creatUser
bool AgendaService::userRegister(std::string userName, std::string password,
                    std::string email, std::string phone) {
  std::list<User> result = storage_->queryUser([&](const User & user)->bool{
    if (userName == user.getName()) {
      return true;
    } else {
      return false;
    }
  });  //  lamda function
  if (result.empty()) {
    storage_->createUser(User(userName, password, email, phone));
    return true;
  } else {
    return false;
  }
}

  // to call deleteUser
bool AgendaService::deleteUser(std::string userName, std::string password) {
  int count = 0;
  count = storage_->deleteUser([&](const User & user)->bool{
    if (userName == user.getName()&&password == user.getPassword()) {
      return true;
    } else {
      return false;
    }
  });  // lamda function

  if (count != 0) {
    //  delete user sponsor Meeting
    deleteAllMeetings(userName);
    //  delete user participator meeting
    storage_->deleteMeeting([&](const Meeting & meeting)->bool {
      if (userName == meeting.getParticipator()) {
        return true;
      } else {
        return false;
      }
    });
    return true;
  } else {
    return false;
  }
}
	// a user can only delete itself
std::list<User> AgendaService::listAllUsers(void) {
  return storage_->queryUser([](const User & user)->bool{
    return true;
  });  //  lamda function
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate) {
  Date D_startDate(Date::stringToDate(startDate));
  Date D_endDate(Date::stringToDate(endDate));
  if (D_startDate >= D_endDate) return false;
  //  startDate should < endDate

  if (!(Date::isValid(D_startDate)&&Date::isValid(D_endDate))) return false;
  //  startDate and endDate should valid
  std::list<Meeting> result_1 = storage_->queryMeeting([&](
    const  Meeting & meeting)->bool{
      if (userName == meeting.getSponsor()&&title == meeting.getTitle()) {
        return true;
      } else {
        return false;
      }
  }); // lamda function
  if (!result_1.empty()) return false;
  // username is sponsor and the some time the title is only one

  std::list<User> allUser = listAllUsers();
  int count = 0;
  std::list<User>::iterator it, end;
  for (it = allUser.begin(), end = allUser.end(); it != end; it++) {
    if (it->getName() == userName||it->getName() == participator) count++;
  }
  if (count < 2) return false;
  //  the username and participator should be register

  std::list<Meeting> result_2 = meetingQuery(userName, startDate, endDate);
  std::list<Meeting> result_3 = meetingQuery(participator, startDate, endDate);
  if (!(result_2.empty()&&result_3.empty())) return false;
  //  the userName and participator should has time;

  storage_->createMeeting(Meeting(userName, participator,
    Date::stringToDate(startDate), Date::stringToDate(endDate), title));

  return true;
}

  //  userName is sponsor or participator
  //  title is title
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
  std::string title) {
  return storage_->queryMeeting([&](const  Meeting & meeting)->bool{
      if ((userName == meeting.getSponsor()||
        userName == meeting.getParticipator())&&title == meeting.getTitle()) {
        return true;
      } else {
        return false;
      }
  });    // lamda function
}


std::list<Meeting> AgendaService::meetingQuery(std::string userName,
  std::string startDate,std::string endDate) {
  return storage_->queryMeeting([&](const Meeting & meeting)->bool{
    Date D_startDate(Date::stringToDate(startDate));
    Date D_endDate(Date::stringToDate(endDate));
    if (Date::isValid(D_startDate)
      &&Date::isValid(D_endDate)
      &&(userName == meeting.getSponsor()||
      userName == meeting.getParticipator())
      &&!(meeting.getStartDate() >= D_endDate||
          meeting.getEndDate() <= D_startDate)) {
    //  fristly   user is sponsor or participator
    //  secondly  startdate <= meeting.startdate or enddate >= meetingenddate
      return true;
    } else {
      return false;
    }
  });  //  lamda function
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  return storage_->queryMeeting([](const Meeting & meeting)->bool{
    return true;
  });  //  lamda function
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
  return storage_->queryMeeting([&](const Meeting & meeting)->bool{
    if (userName == meeting.getSponsor()) {
      return true;
    } else {
      return false;
    }
  });  //  lamda function
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
  std::string userName) {
  return storage_->queryMeeting([&](const Meeting & meeting)->bool{
    if (userName == meeting.getParticipator()) {
      return true;
    } else {
      return false;
    }
  });  //  lamda function
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  int count = 0;
  count = storage_->deleteMeeting([&](const Meeting & meeting)->bool{
    if (userName == meeting.getSponsor()&&title == meeting.getTitle()) {
      return true;
    } else {
      return false;
    }
  });  //  lamda function
  if (count) {
    return true;
  } else {
    false;
  }
}

  //  delete userName all meetings
bool AgendaService::deleteAllMeetings(std::string userName) {
  int count = 0;
  count = storage_->deleteMeeting([&](const Meeting & meeting)->bool{
    if (userName == meeting.getSponsor()) {
      return true;
    } else {
      return false;
    }
  });  //  lamda function
  if (count) {
    return true;
  } else {
    return false;
  }
}

  //  get a storage instance
void AgendaService::startAgenda(void) {
  storage_ = Storage::getInstance();
}

  // delete Storage *
void AgendaService::quitAgenda(void) {
  storage_->sync();
}

