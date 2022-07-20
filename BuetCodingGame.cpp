#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

map<pair<int, int>, bool> vis;
map<pair<int, int>, int> dis;
map< pair<int, int> , pair<int,int> > P;
bool isvalid(char mat[50][50], int x, int y, int r, int c)
{
    if (x < 0 || x >= r || y < 0 || y >= c || vis[{x, y}] || mat[x][y] == '#')
    {
        return false;
    }
    return true;
}

// Up -Left -Down- Right

vector<pair<int,int>> bfs(char mat[50][50], int sx, int sy, int dx, int dy, int n, int m)
{
    int Dx[4] = {-1, 0, 1, 0};
    int Dy[4] = {0, 1, 0, -1};

    queue<pair<int, int> > q;
    vis[{sx, sy}] = true;
    dis[{sx,sy}]=0;
    P[{sx,sy}]={-1,-1};
    q.push({sx, sy});

    while (!q.empty())
    {

        pair<int, int> parent = q.front();
        q.pop();
        int x = parent.first;
        int y = parent.second;

        

    //    cout << x << " " << y << endl;


        // if(x==dx&&y==dy){
        //  //   cout<<"DES"<<endl;
        //     break;
        // }

       

        for (int i = 0; i < 4; i++)
        {
            int X = Dx[i] + x;
            int Y = Dy[i] + y;
            if (isvalid(mat, X, Y, n, m))
            {
                
            dis[{X,Y}]=dis[{x,y}]+1;
             q.push({X, Y});
             vis[{X,Y}]=true;
             P[{X,Y}].first=x;
             P[{X,Y}].second=y;
             

            }
        }
    }
    int stx=dx;
    int sty=dy;

    vector<pair<int,int> > path;

    while(stx!=-1 && sty!=-1){

        path.push_back({stx,sty});
       
       int tx=P[{stx,sty}].first;
       int ty=P[{stx,sty}].second;
        stx=tx;
        sty=ty;
    }

    // for (int i =path.size()-1; i >=0 ; i--)
    // {
    //     cout<<path[i].first<<" "<<path[i].second<<endl;
    // }
    
    
  return path;
    // cout<<"DIS "<<dis[{dx,dy}]<<endl;

}

int main()
{


    int height;
    int width;
    cin >> height >> width; cin.ignore();
    vector<string> maze;
    char mat[50][50];

    for (int i = 0; i < height; i++) {
        string row;
        cin >> row; cin.ignore();
        maze.push_back(row);    
    }

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
           mat[i][j] = maze[i][j];
        }
    }
    
    



    int my_flag_base_r;
    int my_flag_base_c;
    cin >> my_flag_base_r >> my_flag_base_c; cin.ignore();
    int opponent_flag_base_r;
    int opponent_flag_base_c;
    cin >> opponent_flag_base_r >> opponent_flag_base_c; cin.ignore();
    string fire_name;
    int fire_price;
    int fire_damage;
    cin >> fire_name >> fire_price >> fire_damage; cin.ignore();
    string freeze_name;
    int freeze_price;
    int freeze_damage;
    cin >> freeze_name >> freeze_price >> freeze_damage; cin.ignore();
    string mine_name;
    int mine_price;
    int mine_damage;
    cin >> mine_name >> mine_price >> mine_damage; cin.ignore();

    // game loop
    int index = 0,sz,returnIndex = 0;
    vector<pair<int,int>> path;

    map<int,vector<pair<int,int>>>all_path;
    
    bool cond = true;
    while (1) {
        int my_score;
        int opponent_score;
        cin >> my_score >> opponent_score; cin.ignore();
        int my_flag_pos_r;
        int my_flag_pos_c;
        int my_flag_carrier;
        cin >> my_flag_pos_r >> my_flag_pos_c >> my_flag_carrier; cin.ignore();
        int opponent_flag_pos_r;
        int opponent_flag_pos_c;
        int opponent_flag_carrier;
        cin >> opponent_flag_pos_r >> opponent_flag_pos_c >> opponent_flag_carrier; cin.ignore();
        int my_alive_minion_cnt;
        cin >> my_alive_minion_cnt; cin.ignore();
        //edit
        map<int,vector<int>>my_minion,opponent_minion;
        
        for (int i = 0; i < my_alive_minion_cnt; i++) {
            vector<int>temp;
            int id;
            int pos_r;
            int pos_c;
            int health;
            int timeout;
            cin >> id >> pos_r >> pos_c >> health >> timeout; cin.ignore();
            //edit
            temp.push_back(pos_r);
            temp.push_back(pos_c);
            temp.push_back(health);
            temp.push_back(timeout);
            my_minion[id] = temp;
        }
        int visible_minion_cnt;
        cin >> visible_minion_cnt; cin.ignore();
        for (int i = 0; i < visible_minion_cnt; i++) {
            vector<int>temp;
            int id;
            int pos_r;
            int pos_c;
            int health;
            int timeout;
            cin >> id >> pos_r >> pos_c >> health >> timeout; cin.ignore();
            //edit
            temp.push_back(pos_r);
            temp.push_back(pos_c);
            temp.push_back(health);
            temp.push_back(timeout);
            opponent_minion[id] = temp;
        }
        int visible_coin_cnt;
        map<pair<int,int>,int>coin;
        cin >> visible_coin_cnt; cin.ignore();
        for (int i = 0; i < visible_coin_cnt; i++) {
            int pos_r;
            int pos_c;
            cin >> pos_r >> pos_c; cin.ignore();
            coin.insert({{pos_r,pos_c},0});
        }

        //maze;
        //id = 0 , mx = ,my
        


     
       
      
        if(index==0){
           for(auto it: my_minion){
            int id = it.first;
            vector<int> temp;
            temp = it.second;
            int m_x =  temp[0];
            int m_y = temp[1];
            path = bfs(mat, m_y, m_y, opponent_flag_pos_r, opponent_flag_pos_c, height, width);
            reverse(path.begin(),path.end());
            all_path[id] = path;
           }
        }

        if(1)
        for(auto it : all_path){
             vector<pair<int,int> > temp;
             int id = it.first;
             temp = it.second;
             if(index<temp.size()){
                 
                 cout<<"MOVE "<<id<<" "<<temp[index+1].first<<" "<<temp[index+1].second;

                 if(my_alive_minion_cnt!=id+1 ){
                 cout<<" | ";

                }
                  if(my_alive_minion_cnt==id+1){
                 cout<<endl;
              }
              if(temp[index].first == opponent_flag_pos_r && temp[index].second==opponent_flag_pos_c){
                     cond = false;
                   //  break;
              }
                
             }
             

           
        }
        else{
           if(returnIndex == 0){

                for(auto it: my_minion){
                     int id = it.first;
                    vector<int> temp;
                    temp = it.second;
                    int m_x =  temp[0];
                    int m_y = temp[1];
                    path = bfs(mat, m_y, m_y, my_flag_base_r, my_flag_base_c, height, width);
                    reverse(path.begin(),path.end());
                     all_path[id] = path;
                 }
             }
           int index= returnIndex;
           for(auto it : all_path){  
             vector<pair<int,int> > temp;
             int id = it.first;
             temp = it.second;
             if(index<temp.size()){
                 
                 cout<<"MOVE "<<id<<" "<<temp[index+1].first<<" "<<temp[index+1].second;

                 if(my_alive_minion_cnt!=id+1 ){
                       cout<<" | ";

                   }
                  if(my_alive_minion_cnt==id+1){
                    cout<<endl;
                   }
              
                
             }
           }
             returnIndex++;
           


        }

    
       
         
       index++;
        

    }
}