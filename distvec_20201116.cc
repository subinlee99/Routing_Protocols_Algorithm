#include<iostream>
#include <fstream>
#include <string>
#include <vector>

#define INF 999999
#define MAX 101
using namespace::std;
int change_flag=0;
int N;

vector<pair<pair<int, int>, string> > message;
vector<pair< pair<int, int> , int> > changes;
int topology[MAX][MAX];

typedef struct routing_table{
    int dest;
    int next;
    int cost;
} routing_table;
routing_table table[MAX][MAX];

void  print_table(ofstream &file){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (table[i][j].cost != INF){
            //목적지 다음 거리
            //cout << table[i][j].dest << table[i][j].next << table[i][j].cost<<endl;
            file << table[i][j].dest<< " "  << table[i][j].next<< " "  << table[i][j].cost<<endl;
            }
        }
        //cout << endl; ls
        file << endl;
    }
}

void print_result(ofstream &file, int num){
   
    for(int i=0;i<num;i++){
        int s=message[i].first.first;
        int d=message[i].first.second;
        
        vector<int> hop;
        hop.push_back(s);
        
        if(table[s][d].cost != INF){
            while(table[s][d].next != d){
                s=table[s][d].next;
                hop.push_back(s);
            }
            int cost = table[message[i].first.first][d].cost;
            //cout <<"from " <<message[i].first.first<<" to "<<d<<" cost " << cost << " hops ";
            file <<"from " <<message[i].first.first<<" to "<<d<<" cost " << cost <<" hops ";
            for(int j=0;j<(int)hop.size();j++){
                //cout << hop[j] << " ";
                file << hop[j] << " ";
            }
            //cout << "message " << message[i].second <<endl;
            file << "message " << message[i].second <<endl;
        }
        else{ //to route from s to d
            //cout <<"from " <<s<<" to "<<message[i].first.second<<" cost infinite hops unreachable message"<<endl;

            file <<"from " <<s<<" to "<<message[i].first.second<<" cost infinite hops unreachable message "<<message[i].second <<endl;
        }
    }
    //cout << endl;
    file << endl;
}

void exchange(){
    change_flag=0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if(i==j || topology[i][j] == INF) continue; //self or no route -> dont exchange
            for (int k = 0; k < N; k++){
                int tmp = topology[i][j]+ table[j][k].cost;
                if (table[i][k].cost < tmp) continue;
                else if (table[i][k].cost > tmp){
                    table[i][k].next = j;
                    table[i][k].cost = tmp;
                    change_flag=1;
                }
                else{ //tie breaking rule1
                    if (table[i][k].next > j) table[i][k].next = j;
                    change_flag=1;
                }
            }
        }
    }
}

void init_table(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            table[i][j].dest = j;
            if(topology[i][j] != INF){
                table[i][j].next = j;
                table[i][j].cost = topology[i][j];
            }
            else if(i==j){
                table[i][j].next = i;
                table[i][j].cost = 0;
            }
            else{
                table[i][j].next = -1;
                table[i][j].cost=INF;
            }
        }
    }
    
}

int main(int argc, char *argv[]) {

    if (argc != 4){
        cout <<"usage: distvec topologyfile messagesfile changesfile" << endl;
        return 0;
    }

    //open topologyfile file
    fstream input_file1;
    input_file1.open(argv[1]);
    if (!input_file1.is_open()){ //cannot open error
        cout << "Error: open input file." << endl;
        return 0;
    }
    
    //open messagesfile file
    fstream input_file2;
    input_file2.open(argv[2]);
    if (!input_file2.is_open()){ //cannot open error
        cout << "Error: open input file." << endl;
        return 0;
    }
    
    //open changesfile file
    fstream input_file3;
    input_file3.open(argv[3]);
    if (!input_file2.is_open()){ //cannot open error
        cout << "Error: open input file." << endl;
        return 0;
    }
    
    //make output file
    ofstream output_file("output_dv.txt");
    
    //read topologyfile file
    input_file1 >> N; //number of nodes
    for(int i=0;i<N;i++)for(int j=0;j<N;j++){
        topology[i][j]=INF; //init topology graph
        if(i==j) topology[i][j]=0;
    }
    int s, d, w;
    while (input_file1 >> s >> d >> w)
    {
        topology[s][d]=w;
        topology[d][s]=w;
    }
   
    //read message
    while (input_file2 >> s >> d)
    {
        string tmp;
        getline(input_file2, tmp);
        tmp.erase(0,1);
        pair<int, int> p= make_pair(s, d);
        pair<pair<int, int> , string> p1= make_pair(p, tmp);
        message.push_back(p1);
    }
    
    //read Changes file
    while (input_file3 >> s >> d >> w){
        pair<int, int> p= make_pair(s, d);
        pair<pair<int, int> , int> p1= make_pair(p, w);
        changes.push_back(p1);
    }
    
    //init routing table
    init_table();

    //print init status
    for(int j=0;j<N;j++) {
        exchange();
        if(change_flag==0) break;
    }

    print_table(output_file);
    print_result(output_file, (int)message.size());
    
    for(int i=0;i<(int)changes.size();i++){
        //change routing table
        int s = changes[i].first.first;
        int d = changes[i].first.second;
        int w = changes[i].second;
        if(w == -999) w = INF;
        //update topolgy
        topology[s][d]=w;
        topology[d][s]=w;
        
        //initalize routing table
        init_table();

        //exchange routing table
        for(int j=0;j<N;j++) {
            exchange();
            if(change_flag==0) break;
        }
       
        //print table
        print_table(output_file);
        //print message result
        print_result(output_file, (int)message.size());
    }
    cout << "Complete. Output file written to output_dv.txt."<<endl;
    
    //close file
    input_file1.close();
    input_file2.close();
    input_file3.close();
    output_file.close();
    
    return 0;
}
