#include<iostream>
#include<windows.h>
#include<conio.h>
#include"game.h"
using namespace std;
void clear(unsigned char x[][170]){
    for(int i=0;i<42;i++)
        for(int j=0;j<170;j++)
            x[i][j] = ' ';
}
void clear(unsigned char x[][170],user &player){
    for(int i=0;i<42;i++)
        for(int j=0;j<170;j++)
            x[i][j] = ' ';
    
    for(int i=0;i<170;i++){
        x[41][i]='-';
    }
    x[41][0]='l',x[41][1]='i',x[41][2]='f',x[41][3]='e',x[41][4]=':';
    for(int i=0;i<player.life;i++)
        x[41][5+i]=3;
}
void prt(unsigned char x[][170]){
    for(int i=0;i<42;i++)
        for(int j=0;j<170;j++)
            cout << x[i][j];
}
void menu(unsigned char x[][170]){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << R"(
      ::::::::  :::::::::     :::      ::::::::  ::::::::::          ::::::::::: ::::    ::: :::     :::     :::     :::::::::  :::::::::: :::::::::   :::::::: 
    :+:    :+: :+:    :+:  :+: :+:   :+:    :+: :+:                     :+:     :+:+:   :+: :+:     :+:   :+: :+:   :+:    :+: :+:        :+:    :+: :+:    :+: 
   +:+        +:+    +:+ +:+   +:+  +:+        +:+                     +:+     :+:+:+  +:+ +:+     +:+  +:+   +:+  +:+    +:+ +:+        +:+    +:+ +:+         
  +#++:++#++ +#++:++#+ +#++:++#++: +#+        +#++:++#                +#+     +#+ +:+ +#+ +#+     +:+ +#++:++#++: +#+    +:+ +#++:++#   +#++:++#:  +#++:++#++   
        +#+ +#+       +#+     +#+ +#+        +#+                     +#+     +#+  +#+#+#  +#+   +#+  +#+     +#+ +#+    +#+ +#+        +#+    +#+        +#+    
#+#    #+# #+#       #+#     #+# #+#    #+# #+#                     #+#     #+#   #+#+#   #+#+#+#   #+#     #+# #+#    #+# #+#        #+#    #+# #+#    #+#     
########  ###       ###     ###  ########  ##########          ########### ###    ####     ###     ###     ### #########  ########## ###    ###  ########        
)";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; 
    system("pause");
    int i=0,r=20,c=85;
    unsigned char body1[6][13]={
        {220,32 ,32 ,32 ,32 ,32 ,220},
        {220,219,220,220,220,219,220},
        {220,219,219,220,219,219,219,220,219,219,220},
        {219,32 ,219,223,223,223,223,223,219,32 ,219},
        {223,223,32 ,223,223},
        {112,114,101,115,115,32,97,110,121,32,107,101,121}
    };
    unsigned char body2[6][13]={
        {220,32 ,32 ,32 ,32 ,32 ,220},
        {219,32 ,220,219,220,220,220,219,220,32 ,219 },
        {219,219,219,220,219,219,219,220,219,219,219},
        {223,219,223,223,223,223,223,219,223},
        {223,32 ,32 ,32 ,32 ,32 ,32 ,32 ,223},
        {112,114,101,115,115,32,97,110,121,32,107,101,121}
    };
    while(1){
        if(kbhit()){
            clear(x);
            system("cls");
            break;
        }
        system("cls");
        clear(x);
        if(i==0){
                for(int i=0;i<7;i++)
                    x[r-2][c-3+i] = body1[0][i];
                for(int i=0;i<7;i++)
                    x[r-1][c-3+i] = body1[1][i];
                for(int i=0;i<11;i++)
                    x[r][c-5+i] = body1[2][i];
                for(int i=0;i<11;i++)
                    x[r+1][c-5+i] = body1[3][i];
                for(int i=0;i<5;i++)
                    x[r+2][c-2+i] = body1[4][i];
                for(int i=0;i<13;i++)
                    x[r+3][c-6+i] = body1[5][i];
                
                i=1;
                prt(x);
            }else{
                i=0;
                for(int i=0;i<7;i++)
                    x[r-2][c-3+i] = body2[0][i];
                for(int i=0;i<11;i++)
                    x[r-1][c-5+i] = body2[1][i];
                for(int i=0;i<11;i++)
                    x[r][c-5+i] = body2[2][i];
                for(int i=0;i<9;i++)
                    x[r+1][c-4+i] = body2[3][i];
                for(int i=0;i<9;i++)
                    x[r+2][c-4+i] = body2[4][i];
                for(int i=0;i<13;i++)
                    x[r+3][c-6+i] = body1[5][i];
                
                prt(x);
            }
    }
}
void dbg(user &u){
    cout << "nb " << u.nb << endl;
    for(int i=0;i<u.nb;i++){
        cout << "r " << u.bullets[i].r << " c " << u.bullets[i].c << " ishit " << u.bullets[i].ishit << " isdead " << u.bullets[i].isdead << endl;
    }
}
int main(){
    // w:170 h:40
    unsigned char x[42][170];
    int killed=0,tot=2,level=1,r;
    int fire_rate=7,state=0;
    user player;
    enemy1 *e1;
    enemy2 *e2;
    enemy3 *e3;
    int ne1,ne2,ne3;
    random ran;
    clear(x,player);
    system("cls");
    menu(x);
    while(player.life > 0){
        // if(ne1)
        // if(ne1==0){
        //     if(ne2 >0){

        //     }
        // }
        // for(int i=0;i<ne1;i++){
        //     if(e1[i].killed == 2){
        //         delete e1[i].drops;
        //         enemy1 *tmp = new enemy1[ne1-1];
        //         for(int j=0;j<i;j++)
        //             tmp[j] = e1[j];
        //         for(int j=i+1;j<ne1;j++)
        //             tmp[j-1] = e1[j];
        //         delete []e1;
        //         ne1--;
        //         i--;
        //         e1 = new enemy1[ne1];
        //         for(int j=0;j<ne1;j++)
        //             e1[j] = tmp[j];
        //         delete []tmp;
        //     }
        // }
        if(killed == tot){
            state=0;
            level++;
        }
        if(state==0){
            killed=0;
            ne1=0,ne2=0,ne3=0;
            for(int i=7;i<170-15;i+=14)
                ne1++;
            e1 = new enemy1[ne1];
            for(int i=7,j=0;i<170-15;i+=14,j++){
                e1[j].r = 7,e1[j].c = i;
            }

            for(int i=11;i<170-18;i+=17)
                ne2++;
            e2 = new enemy2[ne2];
            for(int i=11,j=0;i<170-18;i+=17,j++){
                e2[j].r = 13,e2[j].c = i;
            }

            for(int i=11;i<170-18;i+=17)
                ne3++;
        
            e3 = new enemy3[ne3];
            for(int i=11,j=0;i<170-18;i+=17,j++){
                e3[j].r = 18,e3[j].c = i;
            }
            state=1;
            tot = ne1 + ne2 + ne3;
        }
        if(killed == tot/2){
            for(int i=0;i<ne1;i++)
                e1[i].descend = 1;
            for(int i=0;i<ne2;i++)
                e2[i].descend = 1;
            for(int i=0;i<ne3;i++)
                e3[i].descend = 1;
        }
        // if(fire_rate==0){
        //     if(ne3 > 0){
        //         r=rand()%ne3;
        //         if(e3[r].killed==0)
        //             e3[r].fire();
        //     }else if(ne2 > 0){
        //         r=rand()%ne2;
        //         if(e2[r].killed==0)
        //             e1[r].fire();
        //     }else if(ne1 > 0){
        //         r=rand()%ne1;
        //         if(e1[r].killed==0)
        //             e1[r].fire();
        //     }
        //     fire_rate = 7-level;
        // }else{
        //     fire_rate--;
        // }
        clear(x,player);
        player.draw(x);
        for(int i=0;i<ne1;i++)
            e1[i].draw(x);
        for(int i=0;i<ne2;i++)
            e2[i].draw(x);
        for(int i=0;i<ne3;i++)
            e3[i].draw(x);

        prt(x);
        while(kbhit()){
            char key = getch();
            player.check(key);
        }
        for(int i=0;i<ne1;i++){
            if(e1[i].collision(player.bullets,player.nb,r)){
                player.remove(r);
                if(e1[i].killed == 1){
                    cout << i << " killed" << endl;
                    killed++;
                    cout << "e1 killed";
                }
            }
        }
        for(int i=0;i<ne2;i++){
            if(e2[i].collision(player.bullets,player.nb,r)){
                player.remove(r);
                if(e2[i].killed == 1){
                    cout << i << " killed" << endl;
                    killed++;
                    cout << "e2 killed";
                }
            }
        }
        for(int i=0;i<ne3;i++){
            if(e3[i].collision(player.bullets,player.nb,r)){
                player.remove(r);
                if(e3[i].killed == 1){
                    // cout << i << " killed" << endl;
                    killed++;
                    // cout << "e3 killed"<<endl;
                    // cout << killed << " " << tot << endl;
                }
            }
        }
        cout.flush();
        // cout << "bullet r" << player.bullets[0].r << " bullet c" << player.bullets[0].c << " enemy r " << e3[0].r <<  " enemy c " << e3[0].c  <<  endl;
        // dbg(player);

        Sleep(150);
        system("cls");
    }
    return 0;
}
