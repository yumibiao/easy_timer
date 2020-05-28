#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include<string>
#include <iostream>
#include <time.h>

#include <io.h>

#include <shlobj.h>
#include <windows.h> //windows
#include <winuser.h>

const int do_u_wanna_shutdown = 0; //shutdown 开关 1为关机，0为不关机

std::ofstream clog;        //日志文件流
std::ifstream cfconfig;

time_t init_time, nowtime; //设置初始化时间
tm *init_time_info, *tminfo;


namespace clibs {
std::string GetExePath(void)  
{  
    char szFilePath[MAX_PATH + 1]={0};  
    GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
    (strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串  
    std::string path = szFilePath;  
  
    return path;  
}  
//获得桌面路径的小玩意
std::string getDesktopPath() {
  LPITEMIDLIST pidl;
  LPMALLOC pShellMalloc;
  char szDir[200];
  if (SUCCEEDED(SHGetMalloc(&pShellMalloc))) {
    if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
      // 如果成功返回true
      SHGetPathFromIDListA(pidl, szDir);
      pShellMalloc->Free(pidl);
    }
    pShellMalloc->Release();
  }

  return std::string(szDir);
}
} // namespace clibs

//定义函数
inline void playtest() {}
inline void init_2();
inline void init_2_pre2();

//log直接打印时间
inline void log_print_time(){
  clog << "[" << tminfo->tm_year%100 << "-" << tminfo->tm_mon +1 << "-"
       << tminfo->tm_mday << " " << tminfo->tm_hour << ":" << tminfo->tm_min
       << ":" << tminfo->tm_sec << "]";
  return;
}
//log打印字符+string
inline void log(std::string s) {
  log_print_time();
  clog<<s<<"\n";
  clog<<std::flush;
  //clog<<std::flush;
  // system("log.txt")
}

int flag = 0;//我也不知道这个flag是啥

inline int checkit(int h1, int m1, int s1, int h2, int m2, int s2) {
  int hour = tminfo->tm_hour;
  int min = tminfo->tm_min;
  int sec = tminfo->tm_sec;
  int hashh1=h1*60*60+m1*60+s1;
  int hashh2=h2*60*60+m2*60+s2;
  int hashnow=hour*60*60+min*60+sec;
  if (hashnow>=hashh1&&hashnow<=hashh2)return 1;
  return 0;
}

namespace task1 {
  int flag = 0;
  inline void init_() {
    if(!do_u_wanna_shutdown)return;
    if (flag)return;
    flag = 1;
    log("flag==1,shutdown command do it!");
    //system("shutdown -s -t 100");
  }
} // namespace task1

//用于直接打开誓词（pptx）文件，并且直接演示
namespace task2{
  int flag=0;
  std::string path;
  inline void doit_(){
    std::string s="\"C:\\Program Files\\Microsoft Office\\root\\Office16\\Powerpnt.exe\" /S \"" + path +"\"";
    std::cout<<s<<"\n";
    WinExec(s.c_str(), SW_SHOWNORMAL);//执行
    log("I open PPT !!!");
    //system(s.c_str());
    //system("\"C:\\Program Files\\Microsoft Office\\root\\Office16\\Powerpnt.exe\" /S \"17班誓词.pptx\"");
  }
  inline void init_(){
    if(flag==1)return;
    flag=1;
    doit_();
  }
}

struct shutdown_task{
  int flag;
  int p;
  inline void init_var(int pp){flag=0;p=pp;}
  inline void init_(){
    if(!do_u_wanna_shutdown)return;
    if(flag)return;
    flag=1;
    log("shutdown command send!");
    system("shutdown -c \"[绿色省电]300s后将关闭计算机=v=\"-s -t 300");
    if(p==-1) return;
    if(rand()%p==0){
      WinExec("ffplay -i -fs alg.flv -autoexit ", SW_SHOWNORMAL);
      //system("ffplay -i -fs alg.flv -autoexit ");
      log("alg!!!!!!!");
    }
  }
};
namespace noon_shutdown_task{
  int flag=0;
  inline void init_(){
    if(!do_u_wanna_shutdown)return;
    if(flag)return;
    flag=1;
    log("shutdown did");
    system("shutdown -s -t 300");
    if(rand()%4==0){WinExec("ffplay -i -fs alg.flv -autoexit ", SW_SHOWNORMAL);  log("alg");}
  }
}
namespace night_shutdown_task{
  int flag=0;
  inline void init_(){
    if(!do_u_wanna_shutdown)return;
    if(flag)return;
    flag=1;
    log("shutdown did");
    system("shutdown -s -t 300");
    if(rand()%6==0){WinExec("ffplay -i -fs alg.flv -autoexit ", SW_SHOWNORMAL); log("alg");}
  }
}
struct shutdown_task class_break;
struct shutdown_task dinner_shutdown_task;
struct shutdown_task test;

inline void chose_func() { //选择函数
  if(checkit(9,42,00,9,42,30)) class_break.init_();
  if(checkit(11,58,00,12,00,00)){noon_shutdown_task::init_();}
  if(checkit(13,30,00,13,43,00)) task2::init_();//幻灯片
  if(checkit(17,26,00,17,26,30)) dinner_shutdown_task.init_();
  if(checkit(21,58,00,22,0,0)){night_shutdown_task::init_();}
  if((nowtime - init_time)%58==0)init_2(),log("updated wallpaper!");
  if((nowtime - init_time)%3600==0)init_2_pre2(),log("changed background wallpaper.");
}
inline void timer() {//一个可爱的死循环
  for (;;) {
    // time_t nowtime;    //时间
    // tm *tminfo;        //时间结构体（指针），可以存储时间
    nowtime = time(0);            //获得当前时间
    tminfo = localtime(&nowtime); //处理时间到结构体:cout << asctime(tminfo);

    std::cout << asctime(tminfo);
    chose_func();
    Sleep(1000);
  }
}
inline void init_var() { //初始化变量
  task1::flag = 0; 
  task2::flag=0;
  class_break.init_var(-1);
  dinner_shutdown_task.init_var(4);
}

inline void debugit(){

}  


inline void creadcfg(){
  cfconfig>>task2::path;//给自动打开幻灯片读入文件名

}
inline void cinit() {
  srand(time(0));
  init_time = time(0);
  init_time_info = localtime(&init_time); //初始化时间
  nowtime = time(0);            //先处理一次时间
  tminfo = localtime(&nowtime); 
  
  clog.open("log.txt", std::ios::app);
  clog.seekp(0, std::ios::end); //日志文件流初始化
  
  cfconfig.open("config.inf");

  
  //---控制台乱码修正
  #ifdef _WIN32
      //http://m.blog.csdn.net/article/details?id=52789570
      //控制台显示乱码纠正      
    // system("chcp 65001"); //设置字符集（使用SetConsoleCP(65001)设置无效，原因未知）
      SetConsoleOutputCP (65001);
      CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。
      info.cbSize = sizeof(info);
      info.dwFontSize.Y = 16; // leave X as zero
      info.FontWeight = FW_NORMAL;
      wcscpy(info.FaceName, L"Consolas");
      SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
  #endif
  //读入配置文件

}

struct Quote{//格言信息
    std::string text;
  }quote[12334];
int quote_count=0;//统计下总共有多少条
int now_quote_num;//记录当前随机到的格言是啥

struct Pic{//图片信息
  std::string name;
}pic[12345];
int pic_count=0;//图片总数
int now_pic_num;//当前图片


//搜索img下的图片文件
inline int init_2_pre1() {//遍历img下的文件
  //目标文件夹=\img
  //目标文件夹路径
  std::string inPath = "img\\*.jpg"; //遍历文件夹下的所有.jpg文件
  //用于查找的句柄
  long handle;
  struct _finddata_t fileinfo;
  //第一次查找
  handle = _findfirst(inPath.c_str(), &fileinfo);
  if (handle == -1)
    return -1;
  do {
    pic_count++;
    pic[pic_count].name = fileinfo.name;
    //找到的文件的文件名
    //  printf("%s\n", fileinfo.name);
  } while (!_findnext(handle, &fileinfo));

  _findclose(handle);
  return 0;
}

//复制文件操作
inline void init_2_pre2(){//复制文件
  DWORD dwError;
  std::string ss;
  ss="img\\";
  int r=rand()%pic_count+1;
  ss+=pic[r].name;

  if (CopyFile(ss.c_str(), "src.jpg", FALSE)) {
    log_print_time();
    clog<<"Copy file successful.From:"<<ss<<"\n";
    //log("From:");
    //log(ss);
    //log("Copy file succeeds.");
  } else {
    dwError = GetLastError();
    switch (dwError) {
    case ERROR_FILE_NOT_FOUND:
      log("The source file does not exist. ");
      //printf("Error: %ld \n", dwError);
      break;
    default:
      log("The new file already exists. ");
      //log("Error: %ld ", dwError);
      break;
    }
  }
}

//虽然全部读入到内存中，但是只占几十个k应该还好。
//为了之后换壁纸不用重新读文件，这样先初始化一遍
inline void init_2_pre3(){//读入格言，避免浪费大量资源
  std::ofstream owo;
  std::ifstream ovo;
  ovo.open("quotes.txt");//打开格言文件
  std::string tmp;
  while(getline(ovo,tmp)){
    if(tmp.size()>112)continue;//132极限似乎？
    quote[++quote_count].text=tmp;//读入
  }
  ovo.close();
}

//生成格言图片，更换壁纸
inline void init_2(){//生成倒计时，读取格言，生成格言，换壁纸
  std::ofstream owo;
  std::ifstream ovo;
  owo.open("countdowntext.txt");

  //time_t hst=1591491600;//设置最终时间UNIX时间
  time_t hst=1594083600;//设置最终时间UNIX时间

  int c_int_day=(hst-nowtime)/(60*60*24);
  int c_int_hour=(hst-nowtime-c_int_day*60*60*24)/(60*60);
  int c_int_min=(hst-nowtime-c_int_day*60*60*24-c_int_hour*60*60)/(60);
  int c_int_sec=(hst-nowtime-c_int_day*60*60*24-c_int_hour*60*60-c_int_min*60);
  c_int_sec=c_int_sec -1 +1;//去掉烦人的警告
  
  
  int c_int_left_hour = 15-tminfo->tm_hour+7;
  int c_int_left_min = 60-tminfo->tm_min;
  if(tminfo->tm_hour>=22)c_int_left_min=0;

  owo<<"距离高考:"<<c_int_day<<"D "<<c_int_hour<<"H "<<c_int_min<<"M\n";
  owo<<"今天剩下:"<<c_int_left_hour<<"h"<<c_int_left_min<<"min";

  
  owo<<std::flush;
  owo.close();
  
  
  owo.open("qu.txt");//生成单条格言
  owo<<quote[now_quote_num=(rand()%quote_count+1)].text;
  owo.close();
  //clog<<quote[now_quote_num].text.size();
  
  //system("owo.cmd");
  //WinExec("owo.cmd", SW_SHOWNORMAL);
  //log("I did the owo.cmd");
  ovo.open("owo.cmd");
  std::string tmp_command;
  while(getline(ovo, tmp_command)){
    if(tmp_command[0]==':'&&tmp_command[1]==':')continue;
    int t=system(tmp_command.c_str());
    log_print_time();
    clog<<"I ran command: \""<<tmp_command<<"\" result:"<<t<<"\n";
  }

  std::string path=clibs::GetExePath();
  path+="\\out.jpg";

  //Sleep(3000);//w等待生成文件
  
  //std::cout<<path;
  
  //---生成日志
  log_print_time();
  clog<<"I get the path:"<<path<<"\n";
  

  //WinExec("bin\\imgmagick\\convert bin\\imgmagick\\src.jpg -transparent white -font fs.ttf -fill black -pointsize 50 -size x150 label:@t.txt -gravity northeast -geometry +100+350 -composite dest.jpg", SW_SHOWNORMAL);
  //system("start \"bin/imgmagick/owo.cmd\"");
  
  //---修改壁纸 
  
  if(SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)path.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE))
  log("I changed the wallpaper!");
  else{
    log("I change wallpaper failed???");
  }
  //exit(0);
}
inline void init_print_ver(){
  std::cout<<"Count_down by.dayi\n";
  std::cout<<"Ver:Beta 0.0086\n";
}
int main() {
  init_print_ver();

  //隐藏命令行窗口
  HWND hwnd;
	hwnd=FindWindow("ConsoleWindowClass",NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
	if(hwnd)
	{
		ShowWindow(hwnd,SW_HIDE);				//设置指定窗口的显示状态
	}
  //WinExec("ffplay -i -fs alg.flv -autoexit -bytes 0 -nodisp", SW_SHOWNORMAL);
  
  int run_test=0;
  std::cout<<++run_test<<"\n";
  cinit();//初始化时间，日志流，配置文件流
  std::cout<<++run_test<<"\n";
  init_var();//初始化变量
  std::cout<<++run_test<<"\n";
  creadcfg();//读取配置文件
  std::cout<<++run_test<<"\n";
  debugit();//调试
  std::cout<<++run_test<<"\n";
  init_2_pre1();//枚举img下的文件
  std::cout<<++run_test<<"\n";
  init_2_pre2();//替换out文件
  std::cout<<++run_test<<"\n";
  init_2_pre3();//初始化格言，读取格言
  std::cout<<++run_test<<"\n";
  init_2();//更换壁纸啥的
  
  timer();//一个死循环，似乎不是特别吃资源
  log("I am died!");
  return 0;
}