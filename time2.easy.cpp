#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include<string>
#include <iostream>
#include <iomanip>
#include <time.h>

#include <io.h>

#include <shlobj.h>
#include <windows.h> //windows
#include <winuser.h>

const int do_u_wanna_shutdown = 0; //shutdown 开关 1为关机，0为不关机 不关机也不会自动放alg.flv

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
  clog << "[" << std::setfill('0') <<std::setw(2) << tminfo->tm_year%100 << "-" << std::setfill('0') <<std::setw(2) << tminfo->tm_mon +1 << "-"
       << std::setfill('0') <<std::setw(2) << tminfo->tm_mday << " " << std::setfill('0') <<std::setw(2) << tminfo->tm_hour << ":" << std::setfill('0') <<std::setw(2) << tminfo->tm_min
       << ":" << std::setfill('0') <<std::setw(2) << tminfo->tm_sec << "]";
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

//一个遗留的shutdown
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

//shutdown结构体，方便一点
struct shutdown_task{
  int flag;
  int p;
  shutdown_task(){flag=0;p=-1;}
  shutdown_task(int pp){flag=0;p=pp;}
  inline void init_var(int pp){flag=0;p=pp;}
  inline void init_(){
    if(!do_u_wanna_shutdown)return;
    if(flag)return;
    flag=1;
    log("shutdown command send!");
    system("shutdown -s -t 300"); //此过程可能有bug
    if(p==-1) return;
    
    //搞事放alg.flv
    if(rand()%p==0){
      std::string s= clibs::GetExePath();
      s = "\""+ s + "\\bin\\ffmpeg\\ffplay.exe\" -i -autoexit -bytes 0 -nodisp "+ "\"" + s + "\\source\\alg.flv" + "\"";
      UINT run_result=WinExec(s.c_str(),SW_SHOWNORMAL);
      if(run_result>31)log("alg!!!!!!!");
      //WinExec("ffplay -i -fs alg.flv -autoexit ", SW_SHOWNORMAL);
      //system("ffplay -i -fs alg.flv -autoexit ");
      
    }
  }
};

//一个遗留的shutdown
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

//一个遗留的shutdown
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

//shutdown函数们
struct shutdown_task class_break;
struct shutdown_task dinner_shutdown_task;
struct shutdown_task test;

inline void chose_func() { //选择函数
  //if(checkit(9,42,00,9,42,30)) class_break.init_();
  if(checkit(11,58,00,12,00,00)){noon_shutdown_task::init_();}
  //if(checkit(13,40,00,13,45,00)) task2::init_();//幻灯片
  //if(checkit(17,26,00,17,26,30)) dinner_shutdown_task.init_();
  if(checkit(21,58,00,22,0,0)){night_shutdown_task::init_();}
  
  if((nowtime - init_time)%59==0 || tminfo->tm_sec == 0 || tminfo->tm_sec == 59)init_2(),log("updated wallpaper!");
  int iitmtcp=(nowtime - init_time)%3600; //it'is time to change paper
  if(iitmtcp==0||iitmtcp==1)init_2_pre2(),log("changed background wallpaper.");
}
inline void timer() {//一个可爱的死循环
  for (;;) {
    // time_t nowtime;    //时间
    // tm *tminfo;        //时间结构体（指针），可以存储时间
    nowtime = time(0);            //获得当前时间
    tminfo = localtime(&nowtime); //处理时间到结构体:cout << asctime(tminfo);

    std::cout << asctime(tminfo);
    chose_func();
    Sleep(950);
  }
}
inline void init_var() { //初始化变量
  srand(time(0));
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
      //来源：
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
  }quote[102334];
int quote_count=0;//统计下总共有多少条
int now_quote_num;//记录当前随机到的格言是啥

struct Pic{//图片信息
  std::string name;
}pic[102345];
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

  if (CopyFile(ss.c_str(), "tmp\\src.jpg", FALSE)) {
    log_print_time();
    clog<<"Copy file successful.From:"<<ss<<"\n";
    log("From:");
    log(ss);
    log("Copy file succeeds.");
  } else {
    dwError = GetLastError();
    switch (dwError) {
    case ERROR_FILE_NOT_FOUND:
      log("The source file does not exist. ");
      break;
    default:
      log("The new file already exists. ");
      break;
    }
  }
}

//虽然全部读入到内存中，但是只占几十个k应该还好。(现在似乎4-5M了..有空再改)
//为了之后换壁纸不用重新读文件，这样先初始化一遍
void init_2_pre3(){//读入格言，避免浪费大量资源
  //std::ofstream owo;
  std::ifstream ovo;
  ovo.open("source/quotes.txt");//打开格言文件
  std::string tmp;
  while(getline(ovo,tmp)){
    if(tmp.size()<3)continue;
    if(tmp.size()>112)continue;//132极限似乎？
    quote[++quote_count].text=tmp;//读入
  }
  ovo.close();
  return;
}

//生成格言图片，更换壁纸
inline void init_2(){//生成倒计时，读取格言，生成格言，换壁纸
  std::ofstream owo;
  std::ifstream ovo;
  owo.open("tmp/countdowntext.txt");

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
  
  owo.open("tmp/countdown2.txt");
  double c_day=(hst-nowtime)/1.0/(60*60*24.0);
  owo<<c_day;
  owo.close();
  
  owo.open("tmp/qu.txt");//生成单条格言
  owo<<quote[now_quote_num=(rand()%quote_count+1)].text;
  owo.close();


  owo.open("tmp/nowtime.txt");
  owo << "[" << std::setfill('0') << std::setw(2) << tminfo->tm_mon + 1 << "-"
      << std::setfill('0') << std::setw(2) << tminfo->tm_mday << " "
      << std::setfill('0') << std::setw(2) << tminfo->tm_hour << ":"
      << std::setfill('0') << std::setw(2) << tminfo->tm_min << "]";
  owo.close();
  //clog<<quote[now_quote_num].text.size();
  
  //system("owo.cmd");
  //WinExec("owo.cmd", SW_SHOWNORMAL);
  //log("I did the owo.cmd");
  
  //执行owo.cmd里面的批处理
  ovo.open("owo.cmd");
  std::string tmp_command;
  while(getline(ovo, tmp_command)){
    if(tmp_command[0]==':'&&tmp_command[1]==':')continue;
    int t=system(tmp_command.c_str());
    log_print_time();
    clog<<"I ran command: \""<<tmp_command<<"\" result:"<<t<<"\n";
  }


  std::string path=clibs::GetExePath();
  path+="\\tmp\\out.jpg";
  
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
  std::cout<<"\n\n";
  std::cout<<"---------------------\n";
  std::cout<<"Count_down by.dayi\n";
  std::cout<<"Ver:Beta 0.009\n";
  std::cout<<"---------------------\n";
  std::cout<<"\n\n";
  std::cout<<std::flush;
}
inline void init_output_print(int s,std::string text){
  if(s==0)std::cout<<"Initing "<<text<<"...\n";
  if(s==1)std::cout<<"Inited "<<text<<"finished.\n";
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
  
  //system("%cd%\\bin\\ffmpeg\\ffplay.exe -i -fs %cd%\\source\\alg.flv -autoexit -bytes 0 -nodisp");
  //WinExec("\\bin\\ffmpeg\\ffplay.exe -i -fs %cd%\\source\\alg.flv -autoexit -bytes 0 -nodisp", SW_SHOWNORMAL);
  // UINT xx=WinExec("notepad.exe",SW_SHOWNORMAL);
  //std::cout<<xx<<"\n";
  //int run_test=0;

  //获得时间，初始化日志流，读取一个奇怪的配置文件
  init_output_print(0,"time,log stream,config");
  //std::cout<<"Initing time,log,config..."<<"\n";
  cinit();//初始化时间，日志流，配置文件流
  //init_output_print(1,"time,log stream,config");
  
  //初始化变量
  init_output_print(0,"variables");
  init_var();//初始化变量
  //init_output_print(1,"variables");

  //读取配置文件
  std::cout<<"Reading config..\n";
  creadcfg();//读取配置文件
  //std::cout<<"Read config finished\n";

  //调试
  std::cout<<"Runing debug functions..\n";
  debugit();//调试
  //std::cout<<"Debug functions ran finshish.\n";

  //图片、一言枚举
  init_output_print(0,"pic,quotes");
  
  std::cout<<"Finding images...\n";
  init_2_pre1();//枚举img下的文件

  std::cout<<"Changing src.jpg...\n";
  init_2_pre2();//替换out文件

  std::cout<<"Reading quotes...\n";
  init_2_pre3();//初始化格言，读取格言
  
  //std::cout<<"wa";
  init_output_print(1,"pic,quotes ");

  //更换壁纸
  std::cout<<"Chaging wallpaper...\n";
  init_2();//更换壁纸啥的
  
  
  init_print_ver();//说一下版本号啦啦啦
  //死循环/计时器
  std::cout<<"Starting timer...\n";

  timer();//一个死循环，似乎不是特别吃资源
  log("I am died!");
  return 0;
}