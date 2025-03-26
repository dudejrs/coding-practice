#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace Proxy {

struct ServiceInterface {
  virtual void operation() = 0;
};

struct Service : ServiceInterface {
  void operation() override {}
};

struct ServiceProxy : ServiceInterface {
  ServiceProxy(ServiceInterface* service) : service(service) {}

  bool check_access() {
    cout << "Proxy : Checking access priror to firing real request" << endl;
    return true;
  }

  void log_access() { cout << "Proxy : Loggint the time of request" << endl; }

  void operation() override {
    if (this->check_access()) {
      this->service->operation();
      this->log_access();
    }
  }

 private:
  ServiceInterface* service;
};

void main() {
  Service service;
  ServiceProxy proxy(&service);
  proxy.operation();
}
};  // namespace Proxy

namespace AttributeProxy {

template <typename T>
struct Property {
  T value;
  Property(const T initial_value) : value(initial_value) {}

  operator T() {
    cout << "some get method doing here" << endl;
    return value;
  }

  T operator=(T new_value) {
    cout << "some set method doing here" << endl;
    return value = new_value;
  }
};

struct Creature {
  Property<int> strength{10};
  Property<int> agility{5};
};

void main() {
  Creature creature;
  creature.agility = 20;
  auto x = creature.strength;
}
};  // namespace AttributeProxy

namespace CachedProxy {

struct VideoInfo {};
struct VideoData {};
struct Video {
  int id;
  VideoInfo info;
  VideoData data;
};

struct ThirdPartyYoutubeLib {
  virtual vector<string> list_videos() = 0;
  virtual VideoInfo get_video_info(int id) = 0;
  virtual void downlaod_video(int id) = 0;
};

struct ThidPartyYoutubeClass : ThirdPartyYoutubeLib {
  vector<string> list_videos() override {
    vector<string> ret;
    return ret;
  };
  VideoInfo get_video_info(int id) override {
    VideoInfo ret;
    return ret;
  };
  void downlaod_video(int id) override {

  };
};

struct CachedYoutubeClass : ThirdPartyYoutubeLib {
  CachedYoutubeClass(ThirdPartyYoutubeLib* service) : service(service) {}

  vector<string> list_videos() override {
    if (!list_cache.size() || need_reset) {
      list_cache = service->list_videos();
    }
    return list_cache;
  };
  VideoInfo get_video_info(int id) override {
    if (!info_cache.size() || need_reset) {
      info_cache[id] = service->get_video_info(id);
    }
    return info_cache[id];
  };
  void downlaod_video(int id) override {
    if (data_cache.find(id) != end(data_cache) || need_reset) {
      service->downlaod_video(id);
    }
  };

 private:
  ThirdPartyYoutubeLib* service;
  vector<string> list_cache;
  map<int, VideoInfo> info_cache;
  map<int, VideoData> data_cache;
  bool need_reset;
};

void main() {}
};  // namespace CachedProxy

namespace VirtualProxy {

struct Image {
  virtual void draw() = 0;
};

// 생성자 호출시에 이미지를 메모리에 적재
struct Bitmap : Image {
  Bitmap(const string& filename) {
    cout << "Loading image from " << filename << endl;
  }

  void draw() override { cout << "Drawing image " << endl; }
};

// 생성자 호출에는 파일이름만 저장해 놓았다가, draw()메소드가 호출 될 떄만
// 메모리에 적재.
struct LazyBitmap : Image {
  LazyBitmap(const string& filename) : filename(filename) {
    cout << "Loading image from " << filename << endl;
  }
  ~LazyBitmap() { delete bitmap; }

  void draw() override {
    if (!bitmap) bitmap = new Bitmap(filename);
    bitmap->draw();
  }

 private:
  Bitmap* bitmap{nullptr};
  string filename;
};

void draw_image(Image& img) {
  cout << "About to draw the image" << endl;
  img.draw();
  cout << "Done drawing the image" << endl;
}

void main() {
  LazyBitmap img{"pokemon.png"};
  draw_image(img);
}
};  // namespace VirtualProxy

namespace CommunicationProxy {
struct Pingable {
  virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable {
  wstring ping(const wstring& message) override { return message + L" pong"; }
};

struct RemotePong : Pingable {
  wstring ping(const wstring& message) override {
    wstring result;
    /* Microsoft REST SDK
            http_client client(U("https//localhsot:9149/"))
            uri_builder builder(U("/api/pingpong/"));
            pplx::task<wstring> task = client.request(
                    methods::GET, builder.to_string())
                    .then([=](http_response r){
                            return r.extract_string();
                    });
            task.wait();
            return task.get();

    */
    return L"";
  }
};

void tryit(Pingable& pp) { wcout << pp.ping(L"ping") << endl; }

void main(void) {
  Pong pp;
  for (int i = 0; i < 3; ++i) {
    tryit(pp);
  }
}
};  // namespace CommunicationProxy

int main(void) {
  Proxy::main();
  AttributeProxy::main();
  CachedProxy::main();
  VirtualProxy::main();
  CommunicationProxy::main();

  return 0;
}