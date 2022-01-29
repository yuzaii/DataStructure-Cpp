//串类的定义
class AString
{
private:
    char *ch;   //串存放数组
    int curLength;    //串的实际长度
    int maxSize;    //存放数组的最大长度. 
    void CheckMem();  //检测内存是否申请成功
public:
    AString();
    AString(int sz);         //构造函数,构造一个最大长度为sz,实际长度为0的字符串
    AString(const char *init);   //构造函数,构造一个最大长度为maxSize,由init初始化的新字符串对象
    AString(const AString &ob);    //复制构造函数,由一个已有的字符串对象ob构造一个新字符串
    ~AString(){delete[] ch;}   //析构函数,释放动态分配的串空间并撤销该字符串对象
    //与字符串对象的比较运算
    int operator == (AString &ob)const {return strcmp(ch,ob.ch) == 0;}  //判断当前实例是否与ob串相等,若相等则返回1,否则返回0
    int operator != (AString &ob)const {return strcmp(ch,ob.ch) != 0;}  //判断当前实例是否与ob串不等,若不等则返回1,否则返回0
    int operator < (AString &ob)const {return strcmp(ch,ob.ch)<0;} //判断当前实例串是否小于ob串,若小于则返回1,否则为0
    int operator > (AString &ob)const {return strcmp(ch,ob.ch)>0;}//判断当前实例串是否大于ob串,若小于则返回1,否则为0
    int operator <= (AString &ob)const {return strcmp(ch,ob.ch)<=0;}//判断当前实例串是否小于等于ob串,若小于等于则返回1,否则为0
    int operator >= (AString &ob)const {return strcmp(ch,ob.ch)>=0;}//判断当前实例串是否大于等于ob串,若大于等于则返回1,否则为0
    //与字符串的比较运算
    int operator == (char *str)const{return strcmp(ch,str) == 0;} //判断当前实例是否与C++串相等,若相等则返回1,否则返回0
    int operator != (char *str)const{return strcmp(ch,str) != 0;}//判断当前实例是否与C++串不相等,若不等则返回1,否则返回0
    int operator < (char *str)const {return strcmp(ch,str)<0;}//判断当前实例是否与小于C++串,若小于则返回1,否则返回0
    int operator > (char *str)const{return strcmp(ch,str)>0;}//判断当前实例是否与大于C++串,若小于则返回1,否则返回0
    int operator <= (char *str)const{return strcmp(ch,str)<=0;}//判断当前实例是否与小于等于C++串,若小于等于则返回1,否则返回0
    int operator >=(char *str)const {return strcmp(ch,str)>=0;}//判断当前实例是否与大于等于C++串,若大于等于则返回1,否则返回0
    AString& operator = (AString &ob);       //将串ob赋值给当前实例.
    AString& operator = (const char *str);   //将字符串赋值给字符串对象
    AString& operator +=(AString &ob);      //若当前实例串长度与ob串长度之和不超过maxSize则把ob串接在当前实例的后面.
    AString& operator +=(const char *str);   //若当前实例串长度与str串长度之和不超过maxSize,则把str串接到串对象后面.
    char& operator[](int i);   //取当前实例的第i个字符返回.
    bool IsEmpty()const{return curLength == 0;}    //判空函数
    int Length() const{return curLength;}    //返回当前实例的实际字符长度.
    //下面主要是常用函数的重载等等，方便各种调用方法
    void SubString(AString &subs,int index,int length);  //从索引index开始截取length长度的字符串返回.
    AString& Remove(int startIndex,int length);   //以索引startIndex开始删除length个字符
    AString& Insert(int pos,const char *value);
     void Clear();   //清空当前字符串对象
    void Output();   //输出
};
//串类的实现
void AString::CheckMem()
{
    if(ch == NULL)
    {
        cerr<<"内存分配失败!\n";
        exit(1);
    }
}

AString::AString()
{
    maxSize = defaultSize;
    curLength = 0;
    ch = new char[maxSize];
    CheckMem();
    ch[0] = '\0';
}

AString::AString(int sz)
{//串构造函数
    maxSize = sz;
    ch = new char[maxSize+1];
    CheckMem();
    curLength = 0;
    ch[0] = '\0';
}

AString::AString(const char *init)
{//串构造函数
    int initLength = strlen(init);
    maxSize = (initLength > defaultSize) ? initLength : defaultSize;
    ch = new char[maxSize+1];
    CheckMem();
    curLength = initLength;
    strcpy(ch,init);
}

AString::AString(const AString &ob)
{//串对象复制构造函数
    maxSize = ob.maxSize;
    ch = new char[maxSize+1];
    CheckMem();
    strcpy(ch,ob.ch);
    curLength = ob.curLength;
}


AString& AString::operator =(AString &ob)
{
    if(&ob != this)//若两个串相等为自我赋值
    {
        Clear();
        curLength = ob.curLength;
        strcpy(ch,ob.ch);
    }
    else
        cout<<"字符串自身赋值出错!\n";
    return *this;
}

AString& AString::operator =(const char *str)
{//字符串赋值
    int strLength = strlen(str);
    maxSize = strLength>maxSize?strLength:maxSize;
    Clear();
    strcpy(ch,str);
    curLength = strLength;
    return *this;
}


AString& AString::operator +=(AString &ob)
{//字符串对象连接
    char *tempCH = ch;
    char *tempOb = ob.ch;
    int addLength = curLength+strlen(tempOb);
    maxSize = maxSize>addLength?maxSize:addLength;
    char *temp = new char[maxSize+1];
    char *tempT = temp;
    while(*tempCH!='\0')
        *tempT++=*tempCH++;
    while(*tempOb!='\0')
        *tempT++=*tempOb++;
    *tempT++='\0';
    Clear();
    strcpy(ch,temp);
    curLength=strlen(ch);
    delete[] temp;
    return *this;
}

AString& AString::operator +=(const char *str)
{//字符串连接到字符串对象
    char *tempCH = ch;
    int addLength = curLength+strlen(str);
    maxSize = maxSize>addLength?maxSize:addLength;
    char *temp = new char[maxSize+1];
    char *tempT = temp;
    while(*tempCH!='\0')
        *tempT++=*tempCH++;
    while(*str!='\0')
        *tempT++=*str++;
    *tempT++='\0';
    Clear();
    strcpy(ch,temp);
    curLength=strlen(ch);
    delete[] temp;
    return *this;
}

char& AString::operator [](int i)
{//读取索引位置上的字符
    if(i<0||i>curLength)
    {
        cerr<<"字符下标越界\n";
        exit(1);
    }
    return ch[i];
}

void AString::SubString(AString &subs,int index,int length)
{
    if(index<0||index+length>maxSize||length<0)
    {
        cerr<<"或索引或者长度越界\n";
        exit(1);
    }
    if(IsEmpty())
        cerr<<"字符串对象为空\n",exit(1);
    else
    {
        char *temp = new char[length+1];
        if(temp==NULL)
        {
            cerr<<"内存分配错误！\n";
            exit(1);
        }
        for(int i=0,j=index;i<length;i++,j++)
        {
            temp[i] = ch[j];
        }
        temp[length] = '\0';
		subs=temp;
    }
}



AString& AString::Remove(int startIndex,int length)
{
    if(startIndex<0||startIndex+length>maxSize||length<0)
    {
        cerr<<"索引或长度越界\n";
        exit(1);
    }
    if(IsEmpty())
        cerr<<"字符串对象为空\n",exit(1);
    for(int i=0;i<curLength-startIndex-length;i++)
    {
        ch[i+startIndex] = ch[i+length+startIndex];
    }
    ch[curLength-length] = '\0';
    curLength=strlen(ch);
    return *this;
}


AString& AString::Insert(int pos,const char *value)
{
    if(pos>curLength||pos<0)
    {
        cerr<<"试图插入的位置越界\n";
        exit(1);
    }
    int addLength = strlen(value) + curLength;

    maxSize = addLength>maxSize?addLength:maxSize;
    char *temp = new char[maxSize+1];
    char *tempCH = ch;
    char *tempH = temp;
    for(int i=0;i<pos;i++)
        *temp++ = *tempCH++;//先将当前对象中插入位置之前的字符复制到tempH指向的内存中
    while(*value!='\0')
        *temp++=*value++;//再将待插入的字符串连接到tempH指向的内存中
    while(*tempCH!='\0')
        *temp++=*tempCH++;//最后将当前对象插入位置之后的字符连接到tempH指向的内存中
    *temp='\0';
    Clear();            //清空当前对象
    
    strcpy(ch,tempH);//将拼接好的字符串复制到实例中
    curLength=strlen(ch);
    return *this;
    
}

void AString::Clear()
{
    delete[] ch;
    ch = new char[maxSize+1];
    CheckMem();//释放内存并重新申请
    ch[0] = '\0';//将串对象置为空
    curLength = 0;
}

void AString::Output()
{
    if(IsEmpty())
        cerr<<"字符串对象为空"<<endl;
    else
        cout<<ch<<endl;
}

