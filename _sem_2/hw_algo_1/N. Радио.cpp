#include <iostream>
#include <cmath>
#include <queue>
#include <map>

class Track;
class Vote;

class Vote {
 private:
  std::string ip_;
  int64_t id_;
  int64_t score_;
  int64_t time_;

 public:
  Vote();
  Vote(std::string, int64_t, int64_t, int64_t);
  std::string GetIp() const;
  int64_t GetId() const;
  int64_t GetScore() const;
  int64_t GetTime() const;
  friend std::istream& operator>>(std::istream&, Vote&);
};

class Track {
 private:
  int64_t id_;
  int64_t score_;

 public:
  Track();
  Track(int64_t, int64_t);
  int64_t GetId() const;
  int64_t GetScore() const;
  bool operator<(const Track&) const;
  friend std::ostream& operator<<(std::ostream&, const Track&);
};

void Input(std::priority_queue<Track>& queue) {
  for (int64_t i = 1; i < 100002; ++i) {
    queue.push(Track(i, 0));
  }
}

void Voting(std::priority_queue<Track>& queue, std::map<std::string, int64_t>& users,
            std::map<int64_t, int64_t>& dict) {
  Vote vote;
  std::cin >> vote;
  if (vote.GetTime() - users[vote.GetIp()] >= 600 || users[vote.GetIp()] == 0) {
    dict[vote.GetId()] += vote.GetScore();
    users[vote.GetIp()] = vote.GetTime();
    queue.push(Track(vote.GetId(), dict[vote.GetId()]));
  }
  std::cout << dict[vote.GetId()] << '\n';
}

void Getting(std::priority_queue<Track>& queue, std::map<int64_t, int64_t>& dict) {
  while (dict[queue.top().GetId()] != queue.top().GetScore()) {
    queue.pop();
  }
  int64_t id = queue.top().GetId();
  std::cout << queue.top();
  queue.pop();
  dict[id] = -1;
  Track a(id, -1);
  queue.push(a);
}

void Computing(std::priority_queue<Track>& queue, std::map<std::string, int64_t>& users,
               std::map<int64_t, int64_t>& dict) {
  while (true) {
    std::string str;
    std::cin >> str;
    if (str == "VOTE") {
      Voting(queue, users, dict);
    } else if (str == "GET") {
      Getting(queue, dict);
    } else {
      break;
    }
  }
}

int main() {
  std::priority_queue<Track> queue;
  std::map<std::string, int64_t> users;
  std::map<int64_t, int64_t> dict;
  Input(queue);
  Computing(queue, users, dict);
  std::cout << "OK\n";
  return 0;
}

Vote::Vote() {
  ip_ = "";
  id_ = 0;
  score_ = 0;
  time_ = 0;
}

Vote::Vote(std::string ip, int64_t id, int64_t score, int64_t time) {
  ip_ = ip;
  id_ = id;
  score_ = score;
  time_ = time;
}

std::string Vote::GetIp() const {
  return ip_;
}

int64_t Vote::GetId() const {
  return id_;
}

int64_t Vote::GetScore() const {
  return score_;
}

int64_t Vote::GetTime() const {
  return time_;
}

std::istream& operator>>(std::istream& is, Vote& vote) {
  is >> vote.ip_ >> vote.id_ >> vote.score_ >> vote.time_;
  return is;
}

Track::Track() {
  id_ = 0;
  score_ = 0;
}

Track::Track(int64_t id, int64_t score) {
  id_ = id;
  score_ = score;
}

int64_t Track::GetId() const {
  return id_;
}

int64_t Track::GetScore() const {
  return score_;
}

bool Track::operator<(const Track& other_track) const {
  return score_ == other_track.score_ ? id_ > other_track.id_ : score_ < other_track.score_;
}

std::ostream& operator<<(std::ostream& os, const Track& track) {
  os << track.id_ << ' ' << track.score_ << '\n';
  return os;
}