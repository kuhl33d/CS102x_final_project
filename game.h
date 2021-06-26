struct bullet
{
    int r;
    int oldr=-1;
    int c;
    int ishit=0;
    int isdead=0;
    void update(unsigned char x[][170],int speed){
        oldr=r;
        r -= speed;
        if(r < 2){
            r=2;
            isdead=1;
        }
    }
    void draw(unsigned char x[][170],int speed=3){
        if(!this->isdead && !this->ishit){
            if(oldr != -1)
                x[oldr-2][c] = 32,x[oldr-1][c]=32,x[oldr][c]=32;
            x[r-2][c] = 178,x[r-1][c] = 177,x[r][c] = 176;
            update(x,speed);
        }
    }
};
struct dropper{
    int r;
    int oldr=-1;
    int c;
    int ishit=0;
    int isdead=0;
    void update(unsigned char x[][170],int speed){
        oldr=r;
        (r>35)? r++:r+=speed;
        if(r > 41){
            r=41;
            isdead=1;
        }
        // else if(r >= 40){
        //     if(x[r][c]!=' '){
        //         ishit=1;
        //         std::cout << "hit " << this << std::endl; 
        //         Sleep(3333);
        //     }
        //     // r-= speed/2;
        //     //speed != 1
        // }
    }
    void draw(unsigned char x[][170],int speed=3){
        if(!this->isdead && !this->ishit){
            if(oldr != -1)
                x[oldr][c] = 32;
            x[r][c] = 178;
            update(x,speed);
        }
    }

};
class random{
    public:
    long double e = 1.7182281828,exp=1,f=1;
    int r;
    int rand(){
        for(int i =0;i<3;i++){
            for(int j = 0;j<=i;j++){
                exp *= e;
            }
            if(exp <0){
                exp *= -1;
            }
            r = exp;
            if(r < 0){
                if(f<0){
                    f=0;
                }
                exp = f;
                r=f;
                f++;
                break;
            }
        }
        return r;
    }
};
class user
{
public:
    int r;
    int c;
    bullet *bullets;
    int nb;
    int sr=3,sc=11;
    int life=3;
    int jump = 0;
    int score;
    unsigned char body[3][11]={
        {220,219,220},
        {220,219,219,219,219,219,219,219,219,219,220},
        {219,219,219,219,219,219,219,219,219,219,219}
    };
    user(){
        score=0;
        nb=0;
        r = 39,c=84;
        life=3;
    }
    ~user(){
        delete bullets;
    }
    void remove(int i){
        bullet *tmp = new bullet[nb-1];
        for(int j=0;j<i;j++){
            tmp[j].r = bullets[j].r;
            tmp[j].c = bullets[j].c;
            tmp[j].oldr = bullets[j].oldr;
            tmp[j].ishit = bullets[j].ishit;
            tmp[j].isdead = bullets[j].isdead;
        }
        for(int j = i+1;j<nb;j++){
            tmp[j-1].r = bullets[j].r;
            tmp[j-1].c = bullets[j].c;
            tmp[j-1].oldr = bullets[j].oldr;
            tmp[j-1].ishit = bullets[j].ishit;
            tmp[j-1].isdead = bullets[j].isdead;
        }
        delete bullets;
        nb--;
        bullets = new bullet[nb];
        for(int j=0;j<nb;j++){
            bullets[j].r = tmp[j].r;
            bullets[j].c = tmp[j].c;
            bullets[j].oldr = tmp[j].oldr;
            bullets[j].ishit = tmp[j].ishit;
            bullets[j].isdead = tmp[j].isdead;
        }
        delete tmp;
    }
    void draw(unsigned char x[][170]){
        if(jump != 0)
            jump--;
        else if(r != 39 && jump == 0)
            r=39;
        for(int i=0;i<3;i++){
            // if(x[r-1][c-1+i] != ' ')
            //     life--;
            x[r-1][c-1+i] = body[0][i];
        }
        for(int i=0;i<11;i++){
            // if(x[r][c-5+i] != ' ')
            //     life--;
            x[r][c-5+i] = body[1][i];
        }
        for(int i=0;i<11;i++){
            // if(x[r+1][c-5+i] != ' ')
            //     life--;
            x[r+1][c-5+i] = body[2][i];
        }
        if(nb != 0){
            for(int i=0;i<nb;i++){
                if(bullets[i].ishit){
                    if(nb != 1){
                        remove(i);
                        i--;
                    }else{
                        delete bullets;
                        nb=0;
                        break;
                    }
                }else if(bullets[i].isdead){
                    if(nb != 1){
                        bullet *tmp = new bullet[nb-1];
                        for(int j=0;j<nb-1;j++){
                            tmp[j].r = bullets[j+1].r;
                            tmp[j].oldr = bullets[j+1].oldr;
                            tmp[j].c = bullets[j+1].c;
                            tmp[j].ishit = bullets[j+1].ishit;
                            tmp[j].isdead = bullets[j+1].isdead;
                        }
                        delete bullets;
                        nb--;
                        i--;
                        bullets = new bullet[nb];
                        for(int j=0;j<nb;j++){
                            bullets[j].r = tmp[j].r;
                            bullets[j].c = tmp[j].c;
                            bullets[j].oldr = tmp[j].oldr;
                            bullets[j].ishit = tmp[j].ishit;
                            bullets[j].isdead = tmp[j].isdead;
                        }
                        delete tmp;
                    }else{
                        delete bullets;
                        nb=0;
                        break;
                    }
                }
            }
            for(int i=0;i<nb;i++)
                bullets[i].draw(x);
        }
    }
    void check(char key,int speed=3){
        if(key == 'a'){
            if(c-sc-speed>=0){
                c-=speed;
            }
        }else if(key == 'd'){
            if(c+sc+speed<=169){
                c+=speed;
            }
        }else if(key == 32){
            fire();
        }else if(key == 'w' && jump == 0 && r == 39){
            r-=3;
            jump=2;
        }
    }
    void fire(){
        if(nb == 0){
            nb++;
            bullets = new bullet[nb];
            bullets[0].r = this->r-2;
            bullets[0].c = this->c;
            bullets[0].ishit = 0;
            bullets[0].isdead = 0;
        }else{
            bullet *tmp = new bullet[nb];
            for(int i=0;i<nb;i++){
                tmp[i].r = bullets[i].r;
                tmp[i].c = bullets[i].c;
                tmp[i].oldr = bullets[i].oldr;
                tmp[i].ishit = bullets[i].ishit;
                tmp[i].isdead = bullets[i].isdead; 
            }
            delete bullets;
            nb++;
            bullets = new bullet[nb];
            for(int i=0;i<nb-1;i++){
                bullets[i].r = tmp[i].r;
                bullets[i].c = tmp[i].c;
                bullets[i].oldr = tmp[i].oldr;
                bullets[i].ishit = tmp[i].ishit;
                bullets[i].isdead = tmp[i].isdead;
            }
            delete tmp;
            bullets[nb-1].r = this->r-2;
            bullets[nb-1].c = this->c;
        }
    }
    // int ishit(dropper *drops,int nd,int &r){
    //     int f=0;
    //     for(int k=0;k<nd;k++){
    //         if((drops[k].r == this->r)&&(drops[k].r == this->r+1) && ((drops[k].c >= this->c-(sc/2)) && (drops[k].c >= this->c-(sc/2))) ){
    //             life--;
    //             f=1;   
    //             r=k;
    //             std::cout << "life--" << std::endl;
    //             Sleep(3333);
    //             return 1;
    //         }
    //     }
    //     return 0; 
    // }
};
class enemy{
    public:
    int r;
    int c;
    int sr=5;
    int sc;
    int anim=0;
    int descend=0;
    int killed=0;
    int nd=0;
    dropper *drops;
    ~enemy(){
        delete drops;
    }
    void remove(int i){
        dropper *tmp = new dropper[nd-1];
        for(int j=0;j<i;j++){
            tmp[j].r = drops[j].r;
            tmp[j].c = drops[j].c;
            tmp[j].oldr = drops[j].oldr;
            tmp[j].ishit = drops[j].ishit;
            tmp[j].isdead = drops[j].isdead;
        }
        for(int j = i+1;j<nd;j++){
            tmp[j-1].r = drops[j].r;
            tmp[j-1].c = drops[j].c;
            tmp[j-1].oldr = drops[j].oldr;
            tmp[j-1].ishit = drops[j].ishit;
            tmp[j-1].isdead = drops[j].isdead;
        }
        delete drops;
        nd--;
        drops = new dropper[nd];
        for(int j=0;j<nd;j++){
            drops[j].r = tmp[j].r;
            drops[j].c = tmp[j].c;
            drops[j].oldr = tmp[j].oldr;
            drops[j].ishit = tmp[j].ishit;
            drops[j].isdead = tmp[j].isdead;
        }
        delete tmp;
    }
    void fire(){
        if(nd == 0){
            nd++;
            drops = new dropper[nd];
            drops[0].r = this->r+2;
            drops[0].c = this->c;
            drops[0].ishit = 0;
            drops[0].isdead = 0;
        }else{
            dropper *tmp = new dropper[nd];
            for(int i=0;i<nd;i++){
                tmp[i].r = drops[i].r;
                tmp[i].c = drops[i].c;
                tmp[i].oldr = drops[i].oldr;
                tmp[i].ishit = drops[i].ishit;
                tmp[i].isdead = drops[i].isdead; 
            }
            delete drops;
            nd++;
            drops = new dropper[nd];
            for(int i=0;i<nd-1;i++){
                drops[i].r = tmp[i].r;
                drops[i].c = tmp[i].c;
                drops[i].oldr = tmp[i].oldr;
                drops[i].ishit = tmp[i].ishit;
                drops[i].isdead = tmp[i].isdead;
            }
            delete tmp;
            drops[nd-1].r = this->r+2;
            drops[nd-1].c = this->c;
        }
    }
    int collision(bullet *b,int &nb,int &ret){
        for(int i=0;i<nb;i++){
            if(b[i].r <= this->r+(this->sr/2) && b[i].r >= this->r-(this->sc/2) && b[i].ishit == 0){
                if(b[i].c <= this->c+(this->sc/2) && b[i].c >= this->c-(this->sc/2) && this->killed==0){
                    if(killed==0)
                        killed=1;
                    ret = i;
                    b[i].ishit = 1;
                    return 1;
                }    
            }
        }
        return 0;
    }
};
class enemy1:public enemy{
    public:
    enemy1(){
        sc=7;
    }
    void operator = (enemy1 &s){
        this->r = s.r;
        this->c = s.c;
        this->anim = s.anim;
        this->killed = s.killed;
        this->nd = s.nd;
        this->drops = new dropper[s.nd];
        for(int i=0;i<s.nd;i++){
            this->drops[i].r = s.drops[i].r;
            this->drops[i].oldr = s.drops[i].oldr;
            this->drops[i].c = s.drops[i].c;
            this->drops[i].ishit = s.drops[i].ishit;
            this->drops[i].isdead = s.drops[i].isdead;
        }
    }
    unsigned char body1[5][7]={
        {220},
        {220,219,219,219,220},
        {219,219,220,219,220,219,219},
        {220,223,220,223,220},
        {223,32 ,223,32 ,223,32 ,223}
    };
    unsigned char body2[5][7]={
        {220},
        {220,219,219,219,220},
        {219,219,220,219,220,219,219},
        {220,223,32 ,223,32 ,223,220},
        {223,32 ,32 ,32 ,223}
    };
    void draw(unsigned char x[][170]){
        // check(x);
        if(killed==0){
            if(anim%2==0){
                x[r-2][c] = body1[0][0];
                for(int i=0;i<5;i++)
                    x[r-1][c-2+i] = body1[1][i];
                for(int i=0;i<7;i++)
                    x[r][c-3+i] = body1[2][i];
                for(int i=0;i<5;i++)
                    x[r+1][c-2+i] = body1[3][i];
                for(int i=0;i<7;i++)
                    x[r+2][c-3+i] = body1[4][i];
            }else{
                x[r-2][c] = body2[0][0];
                for(int i=0;i<5;i++)
                    x[r-1][c-2+i] = body2[1][i];
                for(int i=0;i<7;i++)
                    x[r][c-3+i] = body2[2][i];
                for(int i=0;i<7;i++)
                    x[r+1][c-3+i] = body2[3][i];
                for(int i=0;i<5;i++)
                    x[r+2][c-2+i] = body2[4][i];
            }
            if(descend == 0){
                if(anim == 0){
                    c+=4;
                    anim=1;
                }else{
                    anim=0;
                    c-=4;
                }
            }else if(descend == 1){
                if(anim == 0){
                    anim = 1;
                    c+=4;
                }else if(anim == 1){
                    anim = 2;
                    c-=4;
                }else if(anim == 2){
                    anim = 0;
                    r+=1;
                }
            }
        }else if(killed == 1){
            for(int i=0;i<3;i++){
                x[r-2][c-1+i] = 176;
                x[r+2][c-1+i] = 176;
                x[r-1+i][c-2] = 176;
                x[r-1+i][c+2] = 176;
            }
            x[r-1][c] = 178;
            x[r+1][c] = 178;
            x[r][c-1] = 178;
            x[r][c+1] = 178;
            x[r][c] = 219;
            x[r-1][c-1] = 177;
            x[r+1][c-1] = 177;
            x[r+1][c+1] = 177;
            x[r-1][c+1] = 177;
            killed=2;
        }
        if(nd != 0){
            for(int i=0;i<nd;i++){
                if(drops[i].ishit){
                    if(nd != 1){
                        remove(i);
                        i--;
                    }else{
                        delete drops;
                        nd=0;
                    }
                }else if(!drops[i].isdead){
                    drops[i].draw(x);
                }else if(drops[i].isdead){
                    if(nd != 1){
                        dropper *tmp = new dropper[nd-1];
                        for(int j=0;j<nd-1;j++){
                            tmp[j].r = drops[j+1].r;
                            tmp[j].oldr = drops[j+1].oldr;
                            tmp[j].c = drops[j+1].c;
                            tmp[j].ishit = drops[j+1].ishit;
                            tmp[j].isdead = drops[j+1].isdead;
                        }
                        delete drops;
                        nd--;
                        i--;
                        drops = new dropper[nd];
                        for(int j=0;j<nd;j++){
                            drops[j].r = tmp[j].r;
                            drops[j].c = tmp[j].c;
                            drops[j].oldr = tmp[j].oldr;
                            drops[j].ishit = tmp[j].ishit;
                            drops[j].isdead = tmp[j].isdead;
                        }
                        delete tmp;
                    }else{
                        delete drops;
                        nd=0;
                        break;
                    }
                }
            }
        }
    }
};
class enemy2:public enemy{
    public:
    enemy2(){
        sc=11;
    }
    void operator = (enemy2 &s){
        this->r = s.r;
        this->c = s.c;
        this->anim = s.anim;
        this->killed = s.killed;
        this->nd = s.nd;
        this->drops = new dropper[s.nd];
        for(int i=0;i<s.nd;i++){
            this->drops[i].r = s.drops[i].r;
            this->drops[i].oldr = s.drops[i].oldr;
            this->drops[i].c = s.drops[i].c;
            this->drops[i].ishit = s.drops[i].ishit;
            this->drops[i].isdead = s.drops[i].isdead;
        }
    }
    unsigned char body1[5][11]={
        {220,220,220},
        {220,219,219,219,219,219,219,219,219,219,220},
        {219,219,219,220,220,219,220,220,219,219,219},
        {220,219,223,220,223,219,220},
        {223,223,32 ,32,32,32,32,32,32,223,223}
    };
    unsigned char body2[5][11]={
        {220,220,220},
        {220,219,219,219,219,219,219,219,219,219,220},
        {219,219,219,220,220,219,220,220,219,219,219},
        {220,219,223,223,220,223,223,219,220},
        {223,223,32 ,32 ,32 ,223,223}
    };
    void draw(unsigned char x[][170]){
        // check(x);
        if(killed==0){
            if(anim%2==0){
                for(int i=0;i<3;i++)
                    x[r-2][c-1+i] = body1[0][i];
                for(int i=0;i<11;i++)
                    x[r-1][c-5+i] = body1[1][i];
                for(int i=0;i<11;i++)
                    x[r][c-5+i] = body1[2][i];
                for(int i=0;i<7;i++)
                    x[r+1][c-3+i] = body1[3][i];
                for(int i=0;i<11;i++)
                    x[r+2][c-5+i] = body1[4][i];
            }else{
                for(int i=0;i<3;i++)
                    x[r-2][c-1+i] = body2[0][i];
                for(int i=0;i<11;i++)
                    x[r-1][c-5+i] = body2[1][i];
                for(int i=0;i<11;i++)
                    x[r][c-5+i] = body2[2][i];
                for(int i=0;i<9;i++)
                    x[r+1][c-4+i] = body2[3][i];
                for(int i=0;i<7;i++)
                    x[r+2][c-3+i] = body2[4][i];
            }
            if(descend == 0){
                if(anim == 0){
                    c+=4;
                    anim=1;
                }else{
                    anim=0;
                    c-=4;
                }
            }else if(descend == 1){
                if(anim == 0){
                    anim = 1;
                    c+=4;
                }else if(anim == 1){
                    anim = 2;
                    c-=4;
                }else if(anim == 2){
                    anim = 0;
                    r+=1;
                }
            }
        }else if(killed == 1){
            for(int i=0;i<3;i++){
                x[r-2][c-1+i] = 176;
                x[r+2][c-1+i] = 176;
                x[r-1+i][c-2] = 176;
                x[r-1+i][c+2] = 176;
            }
            x[r-1][c] = 178;
            x[r+1][c] = 178;
            x[r][c-1] = 178;
            x[r][c+1] = 178;
            x[r][c] = 219;
            x[r-1][c-1] = 177;
            x[r+1][c-1] = 177;
            x[r+1][c+1] = 177;
            x[r-1][c+1] = 177;
            killed=2;
        }
        if(nd != 0){
            for(int i=0;i<nd;i++){
                if(drops[i].ishit){
                    if(nd != 1){
                        remove(i);
                        i--;
                    }else{
                        delete drops;
                        nd=0;
                    }
                }else if(!drops[i].isdead){
                    drops[i].draw(x);
                }else{
                    if(nd != 1){
                        dropper *tmp = new dropper[nd-1];
                        for(int j=0;j<nd-1;j++){
                            tmp[j].r = drops[j+1].r;
                            tmp[j].oldr = drops[j+1].oldr;
                            tmp[j].c = drops[j+1].c;
                            tmp[j].ishit = drops[j+1].ishit;
                            tmp[j].isdead = drops[j+1].isdead;
                        }
                        delete drops;
                        nd--;
                        i--;
                        drops = new dropper[nd];
                        for(int j=0;j<nd;j++){
                            drops[j].r = tmp[j].r;
                            drops[j].c = tmp[j].c;
                            drops[j].oldr = tmp[j].oldr;
                            drops[j].ishit = tmp[j].ishit;
                            drops[j].isdead = tmp[j].isdead;
                        }
                        delete tmp;
                    }else{
                        delete drops;
                        nd=0;
                        break;
                    }
                }
            }
        }
    }
};
class enemy3:public enemy{
    public:
    enemy3(){
        sc=11;
    }
    void operator = (enemy3 &s){
        this->r = s.r;
        this->c = s.c;
        this->anim = s.anim;
        this->killed = s.killed;
        this->nd = s.nd;
        this->drops = new dropper[s.nd];
        for(int i=0;i<s.nd;i++){
            this->drops[i].r = s.drops[i].r;
            this->drops[i].oldr = s.drops[i].oldr;
            this->drops[i].c = s.drops[i].c;
            this->drops[i].ishit = s.drops[i].ishit;
            this->drops[i].isdead = s.drops[i].isdead;
        }
    }
    unsigned char body1[5][11]={
        {220,32 ,32 ,32 ,32 ,32 ,220},
        {220,219,220,220,220,219,220},
        {220,219,219,220,219,219,219,220,219,219,220},
        {219,32 ,219,223,223,223,223,223,219,32 ,219},
        {223,223,32 ,223,223}
    };
    unsigned char body2[5][11]={
        {220,32 ,32 ,32 ,32 ,32 ,220},
        {219,32 ,220,219,220,220,220,219,220,32 ,219 },
        {219,219,219,220,219,219,219,220,219,219,219},
        {223,219,223,223,223,223,223,219,223},
        {223,32 ,32 ,32 ,32 ,32 ,32 ,32 ,223}
    };
    void draw(unsigned char x[][170]){
        // check(x);
        if(killed==0){
            if(anim%2==0){
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
            }else{
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
            }
            if(descend == 0){
                if(anim == 0){
                    c+=4;
                    anim=1;
                }else{
                    anim=0;
                    c-=4;
                }
            }else if(descend == 1){
                if(anim == 0){
                    anim = 1;
                    c+=4;
                }else if(anim == 1){
                    anim = 2;
                    c-=4;
                }else if(anim == 2){
                    anim = 0;
                    r+=1;
                }
            }
        }else if(killed == 1){
            for(int i=0;i<3;i++){
                x[r-2][c-1+i] = 176;
                x[r+2][c-1+i] = 176;
                x[r-1+i][c-2] = 176;
                x[r-1+i][c+2] = 176;
            }
            x[r-1][c] = 178;
            x[r+1][c] = 178;
            x[r][c-1] = 178;
            x[r][c+1] = 178;
            x[r][c] = 219;
            x[r-1][c-1] = 177;
            x[r+1][c-1] = 177;
            x[r+1][c+1] = 177;
            x[r-1][c+1] = 177;
            killed=2;
        }
        if(nd != 0){
            for(int i=0;i<nd;i++){
                if(drops[i].ishit){
                    if(nd != 1){
                        remove(i);
                        i--;
                    }else{
                        delete drops;
                        nd=0;
                    }
                }else if(!drops[i].isdead){
                    drops[i].draw(x);
                }else{
                    if(nd != 1){
                        dropper *tmp = new dropper[nd-1];
                        for(int j=0;j<nd-1;j++){
                            tmp[j].r = drops[j+1].r;
                            tmp[j].oldr = drops[j+1].oldr;
                            tmp[j].c = drops[j+1].c;
                            tmp[j].ishit = drops[j+1].ishit;
                            tmp[j].isdead = drops[j+1].isdead;
                        }
                        delete drops;
                        nd--;
                        i--;
                        drops = new dropper[nd];
                        for(int j=0;j<nd;j++){
                            drops[j].r = tmp[j].r;
                            drops[j].c = tmp[j].c;
                            drops[j].oldr = tmp[j].oldr;
                            drops[j].ishit = tmp[j].ishit;
                            drops[j].isdead = tmp[j].isdead;
                        }
                        delete tmp;
                    }else{
                        delete drops;
                        nd=0;
                        break;
                    }
                }
            }
        }
    }
};
// class ufo{
//     public:
//     int r;
//     int c;
//     int life=3;
//     int f=0;
//     unsigned char body[4][13]={
//         {220,220,220},
//         {220,219,219,219,219,219,219,219,220},
//         {220,219,223,219,219,223,219,223,219,219,223,219,229},
//         {223,219,223,223,223,219,223,223,223,219,223}
//     };
//     ufo(){
//         r=3,c=5;
//     }
//     void draw(unsigned char x[][170],int speed){
//         if(f==0){
//             if(c+speed < 170)
//                 c+=speed;
//             else
//                 f=1;
//         }
//         if(f==1){
//             if(c-speed > 0)
//                 c-=speed;
//             else
//                 f=0;
//         }
//         for(int i=0;i<3;i++){
//             if([r-2][c-1+i] != ' ')
//                 life--;
//             x[r-2][c-1+i] = body[0][i];
//         }
//         for(int i=0;i<9;i++){
//             if(x[r-1][c-4+i] != ' ')
//                 life--;
//             x[r-1][c-4+i] = body[1][i];
//         }
//         for(int i=0;i<13;i++){
//             if(x[r][c-6+i] != ' ')
//                 life--;
//             x[r][c-6+i] = body[2][i];
//         }
//         for(int i=0;i<11;i++){
//             if(x[r][c-5+i] != ' ')
//                 life--;
//             x[r][c-5+i] = body[3][i];
//         }
//     }

// };