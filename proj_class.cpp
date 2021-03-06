#include "proj_class.h"
void organizer::setMANA(int i) {
    MANA = i;
}
void organizer::setDECK(char a[]) {
    int i;
    for(i = 0; i < 4; i++)
        card[i] = a[i];
}
void organizer::setFRIEND(char ch, int i, int j, int m) {
    FRIEND[0][m] = ch;
    FRIEND[1][m] = i;
    FRIEND[2][m] = j;
}
void organizer::setENEMY(char ch, int i, int j, int n) {
    ENEMY[0][n] = ch;
    ENEMY[1][n] = i;
    ENEMY[2][n] = j;
}
void organizer::position(void) {
    int i, n, record = 0, j, f1 = 0, f2 = 0, e1 = 0, e2 = 0;
    for(i = 0; i < 30; i++) {
        if(ENEMY[0][i] != 0 && ENEMY[1][i] < 11)
            e1++;	//count the number of ENEMY in x<11
        if(ENEMY[0][i] != 0 && ENEMY[1][i] >= 11)
            e2++;	//count the number of ENEMY in x>=11
        if(FRIEND[0][i] != 0 && FRIEND[1][i] < 11 && FRIEND[2][j] > 11)
            f1++;	//count the number of FRIEND in x<11
        if(FRIEND[0][i] != 0 && FRIEND[1][i] >= 11 && FRIEND[2][j] > 11)
            f2++;	//count the number of FRIEND in x>=11
    }
    for(j = 0; j < 30; j++) { //deal with enemy closed to castle
        if(ENEMY[0][j] == 0)
            break;
        if(ENEMY[2][j] < 24) {
            n = ENEMY[2][j] - 11;
            n = rand() % n + 11;
            if(e1 - f1 > e2 - f2 && e1 > 1) {
                cout <<(ENEMY[1][j]+rand()%4+1) << ' '<< n << '\n';//summon between enemy and castle
                record = 1; //record executing cout
                break;
            } else if(e1 -f1 <= e2 -f2 && e2 > 1) {
                cout <<(ENEMY[1][j]-rand()%4-1) << ' '<< n << '\n';
                record = 1;
                break;
            }
        }
    }
    if(record == 0) {	//generate random position
        if(f1 > f2)
            cout << (rand()%6+3)<< ' ' << (rand()%9+15) << '\n';
        else cout << (rand()%6+13)<< ' ' << (rand()%9+15) << '\n';
    }
}
void organizer::Summon(void) {
    int i, sf = 0;
	for(i = 0; i < 30; i++) { //calculate the number of 4 and 7 
		if(FRIEND[0][i] == 0)
			break;
		if(FRIEND[0][i] == '7' || FRIEND[0][i] == '4') 
			++sf;
	}

    for(i = 0; i < 4; i++) { //9 first
        if(card[i] == '9' && MANA >= 3) {
            cout << "1 9 ";
			position();
            MANA -= 3;
        }
	}
    for(i = 0; i < 4; i++) { //5 second
        if(card[i] == '5' && MANA >= 1) {
            cout << "1 5 ";
			position();
            MANA -= 1;
        }
	}
	if(sf > 3) {
		for(i = 0; i < 4; i++) {//summon 6 if on the deck
			if(card[i] == '6' &&FRIEND[0][2] != 0) {
				if(MANA < 4)
					return;
				else {
					cout << "1 6 ";
					position();
					MANA -= 4;
				}
			}
		}
		for(i = 0; i < 4; i++) {//summon C if on the deck
        	if(card[i] == 'C' && FRIEND[0][2] != 0) {
		     	if(MANA < 7)
			    	return;
			 	else {
					cout << "1 C ";
		        	position();
					MANA -= 7;
				}
			}
		}
	}
   	for(i = 0; i < 4; i++) { //if 7 on the deck, summon 7 first
      	if(card[i] == '7') {
           	if(MANA < 8)
    	        return;
       	     else {
       	       	cout << "1 7 ";
       	   	    position();
         	    MANA -= 8;
			}
        }
    }	
	for(i = 0; i < 4; i++) {//if 4 on the deck, summon 4 
		if(card[i] == '4') {
			if(MANA < 6)
				return;
			else {
				cout << "1 4 ";
				position();
				MANA -= 6;
			}
		}
	}
    for(i = 0; i < 4; i++) { //other force
/*		if(card[i] == '1' && MANA >= 5) {
			cout << "1 1 ";
			position();
			MANA -= 5;
		}*/
        if(card[i] == '2' && MANA >= 3 && FRIEND[0][4] != 0) {
            cout << "1 2 ";
            position();
            MANA -= 3;
        }
        if(card[i] == '3'&& MANA >= 2) {
            cout << "1 3 ";
            position();
            MANA -= 2;
        }
	}
}

void organizer::cleanARRAY(void) {
    int *p;
    for(p = &FRIEND[0][0]; p <= &FRIEND[2][29]; p++)
        *p = 0;
    for(p = &ENEMY[0][0]; p <= &ENEMY[2][29]; p++)
        *p = 0;
}
