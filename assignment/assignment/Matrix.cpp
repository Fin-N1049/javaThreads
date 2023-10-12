#include<iostream>
#include<vector> 
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

class Matrix {
    // To hold the number of rows
    int nb_row;
    
    // To hold the number of columns
    int nb_col;
    
    // A vector to store matrix values
    vector<double> matrix_data;
    
    public:
    // Default constructor
    Matrix() {
        nb_row=0;
        nb_col=0;
    }

    // Constructor to initialize matrix with data randomly
    Matrix(vector<double> matrix_data, int nb_row, int nb_col)
    {
        this->matrix_data=matrix_data;
        this->nb_row=nb_row;
        this->nb_col=nb_col;
        if (this->matrix_data.size() != (this->nb_col * this->nb_row)) {
            cout << "Invalid dimension for the matrix." << endl;
        }
    }
    
    //Constructor to initialize matrix normaly
    Matrix(int nb_row,int nb_col){
        this->nb_row=nb_row;
        this->nb_col=nb_col;
        for(int i=0;i<this->nb_row;i++){
            for(int j=0;j<this->nb_col;j++){
                cout<<"enter element at position ("<<i+1<<","<<j+1<<") : ";
                double element=0;
                cin>>element;
                matrix_data.push_back(element);
            }
        }
        cout<<endl;
    }
    
    //constructure to read from csv
    Matrix(string path){
        ifstream file;
        file.open(path);
        
        //check file exist or not
        if(!file.is_open()) {
            cout<<"Invalid path "<<path<<endl;
        }
        else{
            string num;
            int count=0;
            
            //read a line from the file
            while(getline(file,num)){
              stringstream value(num);
              string num1;
              
              //convert the number present in the line to double and push it into the matrix_data
              while(getline(value,num1,',')){
                  matrix_data.push_back(stod(num1));
                }
                
                //to get the row which is number of line in the file
                count++;
            }
            
            nb_row=count;
            
            //row*column=total elements
            nb_col=matrix_data.size()/nb_row;
        }
        file.close();
    }
    
    //constructure to initialize from vector<vector<>>
    Matrix(vector<vector<double>> matrix){
        nb_col=matrix[0].size();
        nb_row=matrix.size()/nb_col;
        for(int i=0;i<nb_row;i++){
            for(int j=0;j<nb_col;j++){
                matrix_data.push_back(matrix[i][j]);
            }
        }
    }
    
    //to get elements
    double get_element(int i){
        return matrix_data[i];
    }
    
    //to get row
    int row(){
        return nb_row;
    }
    
    //to get column
    int column(){
        return nb_col;
    }
    
    //get shape
    void shape(){
        cout<<nb_row<<"x"<<nb_col<<endl;
    }
    
    //reshape matrix
    void reshape(int nb_row,int nb_col){
        if((nb_row*nb_col)==this->matrix_data.size()){
            this->nb_row=nb_row;
            this->nb_col=nb_col;
        }
        else{
            cout<<"Invalid size out of bound "<<endl;
        }
    }
    
     
    //to print the matrix
    void print(){
        for(int i=0;i<nb_row;i++){
            for(int j=0;j<nb_col;j++){
                cout<<matrix_data[(i*nb_col)+j]<<"  ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    
    //create sub_matrix
    Matrix sub_matrix();
    
    //add row
    void add_row(double row[],int rowsize);
    
    //add row
    void add_row(vector<double> row);
    
    //add column
    void add_col(double column[],int columnsize);
    
    //add column
    void add_col(vector<double> column);
    
    //remove column
    void remove_col(int);
    
    //sort column
    void reorder();
    
    //Transpose
    friend Matrix T(Matrix);
    
    //sort column by index
    void sort_col(int);
    
    //create unitary matrix
    void ID();
    
    //sum of flatened matrix
    double sum();
    
    //avg of flatened matrix
    double avg();
    
    //print first row
    void head(){
        for(int i=0;i<nb_col;i++){
            cout<<matrix_data[i] <<"  ";
        }
        cout<<endl;
    }
    
    //save a csv 
    void to_csv();
    
    //operator overloding matrix multiplication
    Matrix operator *(Matrix);
    
    //operator overloding matrix multiplication
    void operator *=(Matrix);
    
    //operator overloding matrix and scalar multiplication
    Matrix operator *(double);
    
    //operator overloding matrix and scalar multiplication
    void operator *=(double);
    
    //operator overloding matrix addition
    Matrix operator +(Matrix);
    
    //operator overloding Matrix addition
    void operator +=(Matrix);
    
    //operator overloding matrix substraction
    Matrix operator -(Matrix);
    
    //operator overloding Matrix substraction
    void operator -=(Matrix);
    
    //operator overloding scalar division
    Matrix operator /(double);
    
    //operator overloding scalar division
    void operator /=(double);
    
    //operator overloding equal
    bool operator ==(Matrix);
    
    //operator overloding not equal
    bool operator !=(Matrix);
    
};

//add_row
void Matrix::add_row(double row[],int rowsize){
    if(rowsize%this->nb_col==0){
        for(int i=0;i<rowsize;i++){
            this->matrix_data.push_back(row[i]);
        }
        cout<<"Succesfully added "<<endl;
        this->nb_row+=rowsize/this->nb_col;
    }
    else{
        cout<<"Invalid range out of index "<<endl;
    }
}

//add_row
void Matrix::add_row(vector<double> row){
    if(row.size()%this->nb_col==0){
        for(int i=0;i<row.size();i++){
            this->matrix_data.push_back(row[i]);
        }
        cout<<"Succesfully added "<<endl;
        this->nb_row+=row.size()/this->nb_col;
    }
    else{
        cout<<"Invalid range out of index "<<endl;
    }
}

//add_col
void Matrix::add_col(double column[],int columnsize){
    if(columnsize%this->nb_row==0){
        int index=0;
        for(int i=0;i<columnsize;i++){
            index+=nb_col;
            this->matrix_data.insert(this->matrix_data.begin()+index+i,column[i]);
        }
        this->nb_col+=columnsize/this->nb_row;
        cout<<"Succesfully added "<<endl;
    }
    else{
        cout<<"Invalid range out of index "<<endl;
    }
}

//add_col
void Matrix::add_col(vector<double> column){
    if(column.size()%this->nb_row==0){
        int index=0;
        for(int i=0;i<column.size();i++){
            index+=nb_col;
            this->matrix_data.insert(this->matrix_data.begin()+index+i,column[i]);
        }
        this->nb_col+=column.size()/this->nb_row;
        cout<<"Succesfully added "<<endl;
    }
    else{
        cout<<"Invalid range out of index "<<endl;
    }
}

//remove_col
void Matrix :: remove_col(int col_no){
    if(col_no>0 && col_no<=this->nb_col){
        for(int i=0;i<this->nb_row;i++){
            int index=i*this->nb_col+(col_no-1);
            matrix_data.erase(matrix_data.begin()+index);
        }
        this->nb_col=this->nb_col-1;
    }
    else{
        cout<<"Invalid row for deletion "<<endl;
    }
}

//sort by column
void Matrix :: reorder(){
    for(int i=0;i<nb_col;i++){
        for(int k=0;k<nb_row-1;k++){
            int min_idx=k*nb_col+i;
            int index;
            for(int j=0;j<nb_row;j++){
                index=j*nb_col+i;
                if(matrix_data[index]<matrix_data[min_idx]){
                    min_idx=index;
                }
            }
            if(min_idx!=k*nb_col+i){
                double temp=matrix_data[k*nb_col+i];
                matrix_data[k*nb_col+i]=matrix_data[min_idx];
                matrix_data[min_idx]=temp;
            }
        }
    }
}

//sort column by index
void Matrix :: sort_col(int index){
    if(index >0 && index<= nb_col){
        for(int i=0;i<nb_row-1;i++){
            bool swaped=false;
            for(int j=0;j<nb_row-i-1;j++){
                int col_pos1=j*nb_col+index-1;
                int col_pos2=(j+1)*nb_col+index-1;
                if(matrix_data[col_pos1]>matrix_data[col_pos2]){
                    double temp=matrix_data[col_pos2];
                    matrix_data[col_pos2]=matrix_data[col_pos1];
                    matrix_data[col_pos1]=temp;
                    swaped=true;
                }
            }
            if(!swaped){
                break;
            }
        }
    }
}

//Transpose
Matrix T(Matrix a){
    Matrix matrix;
    for(int i=0;i<a.nb_col;i++){
        for(int j=0;j<a.nb_row;j++){
            double value=a.matrix_data[j*a.nb_col+i];
            matrix.matrix_data.push_back(value);
        }
    }
    matrix.nb_col=a.nb_row;
    matrix.nb_row=a.nb_col;
    return matrix;
}

//create unitary matrix
void Matrix :: ID(){
    if(nb_col==nb_row){
        int index=0;
        for(int i=0;i<nb_row;i++){
            for(int j=0;j<nb_col;j++){
                if(j==i*nb_col+index){
                    matrix_data[j]=1;
                    index++;
                }
                else{
                    matrix_data[j]=0;
                }
            }
        }
    }
    else{
        cout<<" Invalid : the given matrix is not a square matrix ";
    }
}

//sum of flatened Matrix
double Matrix::sum(){
    double sum=0;
    for(int i=0;i<matrix_data.size();i++){
        sum+=matrix_data[i];
    }
    return sum;
}

//avg of flatened Matrix
double Matrix :: avg(){
    double avg=0;
    for(int i=0;i<matrix_data.size();i++){
        avg+=matrix_data[i];
    }
    return avg/matrix_data.size();
}

//create sub_matrix
Matrix Matrix::sub_matrix(){
    //for creating random result
    srand(time(0));
    
    Matrix a;
    
    //row and column of new matrix
    int row;
    int column;
    
    //index position from where the sub_matrix to take
    int index;
    
    //for getting row and column
    while(true){
        row=rand();
        column=rand();
        
        //to get the random number between 1 to 10
        row=(row%10)+1;
        column=(column%10)+1;
        int sub_matrix_size=row*column;
        int matrix_size=this->nb_row*this->nb_col;
        if(sub_matrix_size<matrix_size && sub_matrix_size>0){
            break;
        }
    }
    
    //for getting index position
    while(true){
        index=rand();
        
        //to get the random number between 0 to 9
        index=index%10;
        if((this->matrix_data.size()-index)>=row*column){
            break;
        }
    }
    
    //creating sub_matrix
    for(int i=index;i<index+(row*column);i++){
        a.matrix_data.push_back(this->matrix_data[i]);
    }
    a.nb_row=row;
    a.nb_col=column;
    
    return a;
}

//save to csv
void Matrix::to_csv(){
    fstream write;
    write.open("matrix.csv", ios::out | ios::app);
    for(int i=0;i<nb_row;i++){
        for(int j=0;j<nb_col;j++){
            write<<matrix_data[i*nb_col+j]<<",";
        }
        write<<"\n";
    }
}

//Matrix multiplication
Matrix Matrix :: operator *(Matrix a){
    Matrix b;
    if(this->nb_row==a.nb_col){
        b.nb_row=this->nb_col;
        b.nb_col=a.nb_row;
        for(int i=0;i<b.nb_row;i++){
            for(int j=0;j<b.nb_col;j++){
                int index=i;
                double value=0;
                for(int k=0;k<a.nb_col;k++){
                    value+=this->matrix_data[index]*a.matrix_data[(j*a.nb_col)+k];
                    index+=this->nb_col;
                }
                b.matrix_data.push_back(value);
            }
        }
        return b;
    }
    else{
        cout<<"Invalid dimension for matrix multiplication row of 1st == column of 2nd"<<endl;
        
        //returning a null matrix
        return b;
    }
    
}

//Matrix multiplication
void Matrix::operator *=(Matrix a){
    if(this->nb_row==a.nb_col){
        Matrix b;
        b.nb_row=this->nb_col;
        b.nb_col=a.nb_row;
        for(int i=0;i<b.nb_row;i++){
            for(int j=0;j<b.nb_col;j++){
                int index=i;
                double value=0;
                for(int k=0;k<a.nb_col;k++){
                    value+=this->matrix_data[index]*a.matrix_data[(j*a.nb_col)+k];
                    index+=this->nb_col;
                }
                b.matrix_data.push_back(value);
            }
        }
        this->nb_row=b.nb_row;
        this->nb_col=b.nb_col;
        this->matrix_data=b.matrix_data;
    }
    else{
        cout<<"Invalid dimension for matrix multiplication row of 1st == column of 2nd"<<endl;
    }
}

//scalar multiplication
Matrix Matrix:: operator *(double a){
    Matrix b;
    this->nb_row=b.nb_row;
    this->nb_col=b.nb_col;
    
    for(int i=0;i<this->matrix_data.size();i++){
        b.matrix_data[i]=this->matrix_data[i]*a;
    }
    return b;
}

//scalar multiplication
void Matrix:: operator *=(double a){
    for(int i=0;i<this->matrix_data.size();i++){
        this->matrix_data[i]*=a;
    }
}

//Matrix  addition 
Matrix Matrix:: operator +(Matrix a){
    Matrix b;
    if(this->nb_row==a.nb_row && this->nb_col==a.nb_col){
        b.nb_row=this->nb_row;
        b.nb_col=this->nb_col;
        for(int i=0;i<this->matrix_data.size();i++){
            b.matrix_data[i]=this->matrix_data[i]+a.matrix_data[i];
        }
        return b;
    }
    else{
        cout<<"Invalid dimension for addition "<<endl;
        return b;
    }
}

//Matrix addition
void Matrix::operator +=(Matrix a){
    if(this->nb_row==a.nb_row && this->nb_col==a.nb_col){
        for(int i=0;i<this->matrix_data.size();i++){
            this->matrix_data[i]+=a.matrix_data[i];
        }
    }
    else{
        cout<<"Invalid dimension for addition "<<endl;
    }
}

//Matrix  substraction 
Matrix Matrix:: operator -(Matrix a){
    Matrix b;
    if(this->nb_row==a.nb_row && this->nb_col==a.nb_col){
        b.nb_row=this->nb_row;
        b.nb_col=this->nb_col;
        for(int i=0;i<this->matrix_data.size();i++){
            b.matrix_data[i]=this->matrix_data[i]-a.matrix_data[i];
        }
        return b;
    }
    else{
        cout<<"Invalid dimension for substraction "<<endl;
        return b;
    }
}

//Matrix substraction
void Matrix::operator -=(Matrix a){
    if(this->nb_row==a.nb_row && this->nb_col==a.nb_col){
        for(int i=0;i<this->matrix_data.size();i++){
            this->matrix_data[i]-=a.matrix_data[i];
        }
    }
    else{
        cout<<"Invalid dimension for substraction "<<endl;
    }
}

//Matrix division
Matrix Matrix::operator /(double a){
    Matrix b;
    b.nb_row=this->nb_row;
    b.nb_col=this->nb_col;
    for(int i=0;i<this->matrix_data.size();i++){
        double value;
        value=this->matrix_data[i]/a;
        b.matrix_data.push_back(value);
    }
    return b;
}

//Matrix division not returning
void Matrix::operator /=(double a){
    for(int i=0;i<this->matrix_data.size();i++){
        this->matrix_data[i]/=a;
    }
}

//condition operator ==
bool Matrix::operator ==(Matrix a){
    if(this->nb_row==a.nb_row && this->nb_col==a.nb_col){
        bool equal=true;
        for(int i=0;i<this->matrix_data.size();i++){
            if(this->matrix_data[i]!=a.matrix_data[i]){
                equal=false;
                break;
            }
        }
        if(equal==true){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

// condition operator !=
bool Matrix::operator !=(Matrix a){
     if(this->nb_row==a.nb_row && this->nb_col==a.nb_col){
        bool equal=true;
        for(int i=0;i<this->matrix_data.size();i++){
            if(this->matrix_data[i]!=a.matrix_data[i]){
                equal=false;
                break;
            }
        }
        if(equal==true){
            return false;
        }
        else{
            return true;
        }
    }
    else{
        return true;
    }
}


