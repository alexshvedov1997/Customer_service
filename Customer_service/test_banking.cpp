#include<iostream>
#include<cstdlib>
#include<ctime>
#include"queue.h"
const int MIN_PER_HR = 60;

bool newcustomer(double x);

using namespace std;

int main(){
	srand(time(0));
	cout<<"Case study: banking autamstic"<<endl;
	cout<<"Enter the number";
	int qs;
	cin>>qs;
	Queue line(qs);
	cout<<"Enter the number of simulation"<<endl;
	int hours;
	cin>>hours;
	long cycletime = MIN_PER_HR*hours;
	cout<<"Enter the average number of customers per hours"<<endl;
	double perhours;
	cin>>perhours;
	double min_per_cust;
	min_per_cust = MIN_PER_HR/perhours;
	Item temp;
	long turnaways = 0;
	long customers = 0;
	long served = 0;
	long sum_line = 0;
	int wait_time = 0;
	long line_wait = 0;
	for(int cycle = 0; cycle < cycletime; cycle++){
		if(newcustomer(min_per_cust)){
			if(line.isfull()){
			turnaways++;
			}
			else{
			customers++;
			temp.set(cycle);
			line.enqueue(temp);
			}
		}
		if (wait_time <= 0 && !line.isempty()){
			line.dequeue(temp);
			wait_time = temp.ptime();
			line_wait += cycle-temp.when();
			served++;
		}
		if(wait_time>0)
			wait_time--;
		sum_line += line.queuecount();
	}

	if(customers > 0){
		cout<<"customers accept " << customers<< endl;
		cout << " customers served " <<served<<endl;
		cout<<"turnawways: " << turnaways<< endl;
		cout<<"average queue size: "<<endl;
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout<<(double) sum_line/cycletime<<endl;
		cout<<"average wait time: "<<(double) line_wait / served<<"minutes"<<endl;

	}
	else
		cout<<" No customers"<<endl;
	cout<<"Done!"<<endl;

	return 0;
}

bool newcustomer(double x){
	return (rand()*x / RAND_MAX <1);
}