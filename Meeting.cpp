#include "Meeting.h"

/* if you would change the startDate_ and endDate_ the safety way is
** permision that the startDate_ < endDate_ during the changeing
** if startDate_ : 1111-11-11/10:10 endDate_ : 2222-11-11/11:11
** and you change startDate_ to 3333-11-11/10:10 . this false;
** the all the date will be clear;
*/

Meeting::Meeting(): sponsor_(), participator_(), startDate_(),
         endDate_(), title_() {}

Meeting::Meeting(std::string sponsor, std::string participator,
          Date startTime, Date endTime, std::string title):
          sponsor_(sponsor), participator_(participator),
          startDate_(startTime), endDate_(endTime), title_(title) {
  // startdate 2222-11-11/11:11  enddate 1111-11-11/11:11 invalid
  // if invalid the meeting will be clear;
  // all date set 0;
  /*
  if (startDate_ > endDate_) {
    title = sponsor_ = participator = "";
    startDate_ = endDate_ = Date(0, 0, 0, 0, 0);
  }
  */
}

std::string Meeting::getSponsor(void) const {
  return sponsor_;
}

void Meeting::setSponsor(std::string sponsor) {
  sponsor_ = sponsor;
}

std::string Meeting::getParticipator(void) const {
  return participator_;
}

void Meeting::setParticipator(std::string participator) {
  participator_ = participator;
}

Date Meeting::getStartDate(void) const {
  return startDate_;
}

void Meeting::setStartDate(Date startTime) {
  startDate_ = startTime;

  // the betwend startdate and enddate must valid;
  /*
  if (startDate_ > endDate_) {
    title_ = sponsor_ = participator_ = "";
    startDate_ = endDate_ = Date(0, 0, 0, 0, 0);
  }
  */
}

Date Meeting::getEndDate(void) const {
  return endDate_;
}

void Meeting::setEndDate(Date endTime) {
  endDate_ = endTime;
  /*
  if (startDate_ > endDate_) {
    title_ = sponsor_ = participator_ = "";
    startDate_ = endDate_ = Date(0, 0, 0, 0, 0);
  }
  */
}

std::string Meeting::getTitle(void) const {
  return title_;
}

void Meeting::setTitle(std::string title) {
  title_ = title;
}

