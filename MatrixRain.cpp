#include<vector>
#include<unistd.h>
#include<sys/ioctl.h>
#include<iostream>
#include<random>
#define green "\033[0;32m"
#define white "\033[1;37m"
#define L 28
void GetWH(int* w,int* h){//the code was copied from https://stackoverflow.com/a/1022961 and edited by me
 struct winsize ww;
 ioctl(STDOUT_FILENO,TIOCGWINSZ,&ww);
 *h=(int)(ww.ws_row);
 *w=(int)(ww.ws_col);}
int GetRandomIntInRange(int a,int b){//the code was copied from https://stackoverflow.com/a/7560564 and edited by me
 std::random_device rd;
 std::mt19937 gen(rd());
 std::uniform_int_distribution<> distr(a,b);
 return distr(gen);}
char random_char(){
 return (char)GetRandomIntInRange(33,126);}
int main(){
 srand(time(0));

 int w,h,x,y,i;
 std::vector<std::vector<int>> rain;
 std::vector<std::vector<char>> screen={};
 std::vector<std::vector<char>> light={};
 for(;;){
  GetWH(&w,&h);

  while(screen.vector::size()<w){
   screen.push_back({});
   light .push_back({});}
  for(x=0;x<w;x++)
   while(screen[x].vector::size()<w){
    light [x].push_back( 0 );
    screen[x].push_back('0');}
  while(screen.vector::size()>w){
   screen.pop_back();
   light .pop_back();}
  for(x=0;x<w;x++)
   while(screen[x].vector::size()>h){
    screen[x].pop_back();
    light [x].pop_back();}

  std::string outp="";
  for(y=0;y<h;y++){
   for(x=0;(y<(h-1))?(x<w):(x<(w-1));x++){
    switch(light[x][y]){
     case L :{
      outp+=white;
      outp+=screen[x][y];
      outp+=green;
      break;}
     case 0 :{
      outp+=' ';
      break;}
     default:{
      outp+=screen[x][y];}}
    if(light[x][y]>0)
     light[x][y]--;}
   outp+='\n';}
  outp.pop_back();

  std::cout<<(char)0x1B<<"[0;0f"<<green<<outp<<"\033[0m"<<std::flush;

  if(rand()<((long long)40000*RAND_MAX/w)){
   screen
    [(int)((((unsigned long long int)rand())*w)/((unsigned long long int)RAND_MAX+1))]
    [(int)((((unsigned long long int)rand())*h)/((unsigned long long int)RAND_MAX+1))]
     =random_char();}

  if(rand()<((long long)4000*RAND_MAX/(w*2))){
   int qp;
   for(;;){
    qp=(int)((((unsigned long long int)rand())*w)/RAND_MAX);
    if((qp%2)==1)
     break;}
    rain.push_back({qp,-1});}

  for(i=0;i<rain.vector::size();i++){
   if(rain[i][1]>=0 && rain[i][1]<h){
    screen[rain[i][0]][rain[i][1]]=random_char();
    light [rain[i][0]][rain[i][1]]=L;}
   rain[i][1]++;
   if(rain[i][1]>h)
    rain.erase(rain.begin()+i);}
  usleep(50000);}}
