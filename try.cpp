#include<iomanip>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
string user_Name;
int PIN_num;
float temp_rec[12][30][2]; 
void data();
void admin();
void user();
void User_UI();
void Admin_UI();
void welcome();
void low_month_day(float *low);
void high_month_day( float *high);
void high_low_avg_temp_month(int month, float *high, float *low, float *avg );
void high_low_temp_day (int month, int date, float *high, float *low);
void month_name ( int temp);
void CSV();
void record();
void ui();
void Clear_data();
void random();
void avtable();
void data_table();
void UName_Pin();
void check(string User_Name, int PIN);
void Change_PIN_UserName();
void Thank_u();
void data(){
    ifstream myFile;
    float final;
    
    myFile.open("test2.csv");
    
    
        for(int i=0; i<12; i++){
            for(int j=0; j<30; j++){
                for(int k=0; k<2; k++){
                    string ff;
                    getline(myFile, ff, ',');
                    istringstream(ff)>>final;
                    temp_rec[i][j][k] = final;
                }
            }
        }
}

void high_low_temp_day (int month, int date, float *high, float *low){
    data(); // call a function data to get the data int the temp_rec array
    *high  = temp_rec[month-1][date-1][1];
    *low  = temp_rec[month-1][date-1][0];
}
void check(string User_Name, int PIN){
    
}
void month_name ( int mnum){
      string mname;
    
     switch (mnum)
    {
    case 0:
        mname="january";
                break;
     case 1:
        mname="february";
                break;
      case 2:
        mname="march";
                break; 
      case 3:
        mname="april";
                break;  
      case 4:
        mname="may";
                break; 
      case 5:
        mname="june";
                break; 
      case 6:
        mname="july";
                break; 
       case 7:
        mname="august";
                break;
      case 8:
        mname="september";
                break;   
       case 9:
        mname="october";
                break; 
       case 10:
        mname="november";
                break;  
      case 11:
        mname="december";
                break;             
    }
    cout<<left<<setw(9)<<mname;
}

void random(){
    float temp;
         for(int i =0; i<12; i++){
            for(int j=0; j<30; j++){
                for(int k=0; k<2; k++){
                float y = float(150 + rand()%150)/10;
                temp_rec[i][j][k]=y;
                }
                if(temp_rec[i][j][0]>temp_rec[i][j][1]){
                    temp = temp_rec[i][j][1];
                    temp_rec[i][j][1] = temp_rec[i][j][0];
                    temp_rec[i][j][0] = temp;  
                }
            }
        }

        CSV();
}
void Clear_data(){
    
    for(int i =0; i<12; i++){
        for(int j=0; j<30; j++){
            for(int k=0; k<2; k++){
                float y = 0;
                temp_rec[i][j][k]=y;
            }
        }

    }
    CSV();
}
void CSV(){
    ofstream myFile;
    myFile.open("test2.csv");
    for(int i=0; i<12; i++){
        for(int j=0; j<30; j++){
            for(int k=0; k<2; k++){
                myFile<<temp_rec[i][j][k]<<",";
            }
            myFile<<endl;
        }
    }
}

void record(){
    data();
    int month, date;
    float high, low;
    cout<<"Enter the month number: ";
    cin>>month;
    cout<<"Enter the date number: ";
    cin>>date;
    if(date<=30&&date>=1&&month>=1&&month<=12){
        cout<<"High value: ";
        cin>>high;
        cout<<"Lowest value: ";
        cin>>low;
        if(high>=low){
            if(high<=29.9)
            {
                if(low>=15){

                temp_rec[month-1][date-1][0] = low;
                temp_rec[month-1][date-1][1] = high;
                }
                else
                {
                    cout<<"The Lowest value is Too low";
                }
                
            }
            else{
                cout<<"The highest Value is too High";
            }
        }
        else{
            cout<<"Incorect Value";
        }
    }
    else
    {
        cout<<"Invalid Input";
    }
    
}
void Change_PIN_UserName(){
    UName_Pin();
    string user_name, New_Uname;
    int pin, New_pin;
    cout<<"Enter the Old User Name: ";
    cin>>user_name;
    cout<<"Enter the Old PIN: ";
    cin>>pin;
    if(pin==PIN_num && user_name == user_Name){
        cout<<"Enter the new User Name: ";
        cin>>New_Uname;
        cout<<"Enter the new PIN: ";
        cin>>New_pin;
        ofstream User_Name, PIN;
        User_Name.open("UserName.csv");
        User_Name<<New_Uname<<",";
        PIN.open("PIN.csv");
        PIN<<New_pin;
    }
    else{
        cout<<"Sorry you entered wrong value!";
    }
}

void welcome()
{
system("color 05");

	ifstream ifs ("welcome.txt");
	string Lines = "";

    if (ifs)
    {
		while (ifs.good ())
		{
	    	string TempLine;
	    	getline (ifs , TempLine);
	    	TempLine += "\n";

	    	Lines += TempLine;
		}

	cout << Lines;


	}

}
void low_month_day(float *low){
    data();
    *low =temp_rec[0][0][0];
    for(int i=0;i<12; i++)
        for(int j=0; j<30; j++)
            for(int k=0; k<2; k++)
                    if(*low>temp_rec[i][j][k])
                            *low=temp_rec[i][j][k];


}

void high_low_avg_temp_month(int month, float *high, float *low, float *avg ){
    data(); // call a function data to get the data int the temp_rec array
    //Declare empty array to store all the high and low values of a month
    float hi[30] = {};
    float lo[30] = {};
    //Declare float variables to store the averages of a daily temperature
    float sum=0, avg_day;

    for(int i=0; i<30; i++){
        // store the high and low temperature values in the empty array 
            hi[i] = temp_rec[month-1][i][1];
            lo[i] = temp_rec[month-1][i][0];
    }
    // finding the lowest and highest values by compering all the high and low temperature of a day
    //assume the first value is the highest and the lowest
    *high = hi[0];
    *low = lo[0];
    for(int i=0; i<30; i++){
        if(hi[i]>*high){
            *high = hi[i];
        }
        if(lo[i]<*low){
            *low = lo[i];
        }
    }
    // finding the average temperatures for a given month by summing up all the tempratures in the month.
    for(int i=0; i<30; i++){
        for(int j=0; j<2; j++){
             sum=sum+temp_rec[month-1][i][j];
           }
    }
    *avg=sum/60;
}


void high_month_day( float *high){
    data();
    *high=temp_rec[0][0][0];
    for(int i=0;i<12; i++)
        for(int j=0; j<30; j++)
            for(int k=0; k<2; k++)
                    if(*high<temp_rec[i][j][k])
                            *high=temp_rec[i][j][k];

}
void admin(){
    UName_Pin();
    int pin;
    string userName;
    cout<<"Enter the User name: ";
    cin>>userName;
    cout<<"Enter the PIN: ";
    cin>>pin;
    if(pin==PIN_num && userName == user_Name){
        Admin_UI();
    }
    else{
        cout<<"Bad";
    }
}

void data_table(){
float sum=0;   
data();
cout<<"--------------------------------------------"<<endl;
cout<<left<<setw(11)<<"DAY"<<" || "<<left<<setw(7)<<"LOW"<<"||"<<" "<<left<<setw(7)<<"HIGH"<<"||"<<" "<<left<<setw(7)<<"AVERAGE"<<"||"<<endl;
cout<<"--------------------------------------------"<<endl;
for(int mnum=0; mnum<12; mnum++){
    for(int j=0; j<30; j++){   
    month_name(mnum);
    cout<<" "<<left<<setw(2)<<j+1;
    cout<<"|| "<<left<<setw(7)<<temp_rec[mnum][j][0]<<"||"<<" "<<left<<setw(7)<<temp_rec[mnum][j][1]<<"||"<<" "<<left<<setw(7)<<(temp_rec[mnum][j][1]+temp_rec[mnum][j][0])/2<<"||"<<endl;
    cout<<"--------------------------------------------"<<endl;                                                            
    }
        }
    
}

void avtable(){

 float sum=0;   
data();
cout<<"-------------------------------"<<endl;
cout<<"||"<<left<<setw(4)<<"NUMBER"<<"|| "<<left<<setw(9)<<"MONTH"<<"|| "<<left<<setw(7)<<"AVERAGE"<<"||"<<endl;
cout<<"-------------------------------"<<endl;
for(int mnum=0; mnum<12; mnum++){
 sum=0; 
    for(int j=0; j<30; j++){
        for(int k=0; k<2; k++){
            sum=sum+temp_rec[mnum][j][k];
            
        }
    }     
            
           
    cout<<"|| "<<left<<setw(4)<< mnum+1<<"|| ";
    month_name(mnum);
    cout<<"|| "<<left<<setw(7)<<sum/60<<"||"<<endl;
    cout<<"-------------------------------"<<endl;                                                            

        }
    
}
void User_UI(){
    welcome();
    int choose, month, date,mnum;
    float avg, high, low;
    bool exit= false;
    while(exit==false){
    cout<<"\n\npress \n\n";
    cout<<"\t1. \tto see the entire daily data in table. \n";
    cout<<"\t2. \tFor Any day's high and low temperature. \n";
    cout<<"\t3. \tFor Any month high, low and average temperatures for a given month \n";
    cout<<"\t4. \tFor Month and day with the highest temperature\n";
    cout<<"\t5. \tFor Month and day with the lowest temperature. \n";
    cout<<"\t6. \tFor All months average temperature to he printed in table format\n";
    cout<<"\t7. \tto exit\n";
    cin>>choose;
    switch (choose)

    {
        case 1:
        data_table();
        break;
        case 2:
            cout<<"enter the month: ";
            cin>>month;
            if(month>0 && month<=12){
            cout<<"enter the date: ";
            cin>>date;
            if(date>0 && date<=30){
            // we pass the variables by Reference 
            high_low_temp_day(month, date, &high, &low);
            cout<<date<<"\\"<<month<<"\\"<<"2010 highst temperature is "<<high<<" oC and the lowest is "<<low<<" oC"<<endl;// dispaly the result
            }
            }
            else{
               cout<<"invalid input !!"<<endl;   
            }
        break;
        case 3: 
            cout<<"Enter the month: ";
            cin>>month;
            if(month>0 && month<=12){
            high_low_avg_temp_month(month, &high, &low, &avg);
            cout<<"The highest temperature in "<<"month "<< month <<" is "<<high<<" oC"<<endl;
            cout<<"The lowest temperature in "<<"month "<< month <<" is "<<low<<" oC"<<endl;
            cout<<"The average temperature in "<<"month "<< month <<" is "<<avg<<" oC"<<endl;
            }
            else{
                cout<<"invalid input !!"<<endl;
            }
        break;
        case 4: 
            high_month_day(&high);
                cout<<"\nThe highest temperature in entire year is: "<<high<<"\n\n";
                cout<<"this temprature was recorded in:\n\n";
                for(int i=0; i<12; i++){
                    for(int j=0; j<30; j++){
                        for(int k=0; k<2; k++){
                            if(temp_rec[i][j][k]==high){
                            cout<<j+1<<" / "<<i+1<<" / 2010"<<endl;      
                            }
                        }
                    }
                
            }
        break;
        case 5: 
            low_month_day(&low);
            cout<<"\nThe lowest temperature in entire year is: "<<low<<"\n";
             cout<<"this temprature was recorded in:\n\n";
                for(int i=0; i<12; i++){
                    for(int j=0; j<30; j++){
                        for(int k=0; k<2; k++){
                            if(temp_rec[i][j][k]==low){
                            cout<<j+1<<" / "<<i+1<<" / 2010"<<endl;   
                            }
                        }
                    }
                }
        break;
        case 6:
       avtable(); 
        break;
        case 7:
        system ("CLS");
        Thank_u();
        exit=true;
        break;
        default:
        cout<<"invalid input. please try again!"<<endl;
        break;
       
    }
    if(choose!=7){
     system ("PAUSE");
     system ("CLS");
    } 
 } 
}
void Admin_UI(){
    welcome();
    int choose, month, date,mnum;
    float avg, high, low;
    bool exit= false;
    while(exit==false){
    cout<<"\n\npress \n\n";
    cout<<"\t1. \tRecord Data. \n";
    cout<<"\t2. \tRandom Data. \n";
    cout<<"\t3. \tClear the Data. \n";
    cout<<"\t4. \tTo see the entire daily data in table. \n";
    cout<<"\t5. \tFor Any day's high and low temperature. \n";
    cout<<"\t6. \tFor Any month high, low and average temperatures for a given month \n";
    cout<<"\t7. \tFor Month and day with the highest temperature\n";
    cout<<"\t8. \tFor Month and day with the lowest temperature. \n";
    cout<<"\t9. \tFor All months average temperature to he printed in table format.\n";
    cout<<"\t10. \tTo Change User Name and PIN.\n";
    cout<<"\t11. \tTo exit\n";
    cin>>choose;
    switch (choose)

    {   case 1:
            record();
            CSV();
        break;
        case 2:
            random();
        break;
        case 3:
            Clear_data();
        break;
        case 4:
        data_table();
        break;
        case 5:
            cout<<"enter the month: ";
            cin>>month;
            if(month>0 && month<=12){
            cout<<"enter the date: ";
            cin>>date;
            if(date>0 && date<=30){
            // we pass the variables by Reference 
            high_low_temp_day(month, date, &high, &low);
            cout<<date<<"\\"<<month<<"\\"<<"2010 highst temperature is "<<high<<" oC and the lowest is "<<low<<" oC"<<endl;// dispaly the result
            }
            }
            else{
               cout<<"invalid input !!"<<endl;   
            }
        break;
        case 6: 
            cout<<"Enter the month: ";
            cin>>month;
            if(month>0 && month<=12){
            high_low_avg_temp_month(month, &high, &low, &avg);
            cout<<"The highest temperature in "<<"month "<< month <<" is "<<high<<" oC"<<endl;
            cout<<"The lowest temperature in "<<"month "<< month <<" is "<<low<<" oC"<<endl;
            cout<<"The average temperature in "<<"month "<< month <<" is "<<avg<<" oC"<<endl;
            }
            else{
                cout<<"invalid input !!"<<endl;
            }
        break;
        case 7: 
            high_month_day(&high);
                cout<<"\nThe highest temperature in entire year is: "<<high<<"\n\n";
                cout<<"this temprature was recorded in:\n\n";
                for(int i=0; i<12; i++){
                    for(int j=0; j<30; j++){
                        for(int k=0; k<2; k++){
                            if(temp_rec[i][j][k]==high){
                            cout<<j+1<<" / "<<i+1<<" / 2010"<<endl;      
                            }
                        }
                    }
                
            }
        break;
        case 8: 
            low_month_day(&low);
            cout<<"\nThe lowest temperature in entire year is: "<<low<<"\n";
             cout<<"this temprature was recorded in:\n\n";
                for(int i=0; i<12; i++){
                    for(int j=0; j<30; j++){
                        for(int k=0; k<2; k++){
                            if(temp_rec[i][j][k]==low){
                            cout<<j+1<<" / "<<i+1<<" / 2010"<<endl;   
                            }
                        }
                    }
                }
        break;
        case 9:
       avtable(); 
        break;
        case 10:
            Change_PIN_UserName();
        break;
        case 11:
        system ("CLS");
        Thank_u();
        exit=true;
        break;
        default:
        cout<<"invalid input. please try again!"<<endl;
        break;
       
    }
    if(choose!=11){
     system ("PAUSE");
     system ("CLS");
    } 
 } 
}

int main(){
    ui();
}

void ui(){
    int num;
    cout<<"1: Admin\n";
    cout<<"2: User\n";
    cin>>num;

    if(num==1){
        admin();
    }
    else if(num==2)
    {
        User_UI();
    }
}   
void Thank_u(){

	ifstream ifs ("Thank u.txt");
	string Lines = " ";

    if (ifs)
    {
		while (ifs.good ())
		{
	    	string TempLine;
	    	getline (ifs , TempLine);
	    	TempLine += "\n";

	    	Lines += TempLine;
		}

	cout << Lines;

	}
    cout<<"\n\t  |\t\t\t\t\t\t\t";
    ifs.close ();

    exit(0);
}

void UName_Pin(){
    ifstream User_Name;
    ifstream PIN;
    User_Name.open("UserName.csv");
    PIN.open("PIN.csv");
    getline(User_Name, user_Name, ',');
    PIN>>PIN_num;
}