//gawa struct for x y for points and slope
//gawa function search to right search to the left
//chebyshev
//k-mean cluster algo
//cache in DataDigital for continuous access

//malloc check
//getvalue check cache

//put in a function circle loop


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>


FILE* Snapshot;
FILE* csvfile;
FILE* circlefile;

//#define DBGFLAG 1
//#define LOPFLAG 1
//#define CIRFLAG 1

#ifdef  CIRFLAG
    #define CIRPRINT(...) fprintf(circlefile,__VA_ARGS__);
#else
    #define CIRPRINT(...)
#endif
#ifdef  LOPFLAG
    #define LOPPRINT(...) fprintf(Snapshot,  __VA_ARGS__);
#else
    #define LOPPRINT(...)
#endif
#ifdef  DBGFLAG
    #define DBGPRINT(...) fprintf(Snapshot,  __VA_ARGS__);
#else
    #define DBGPRINT(...)
#endif
#define INFPRINT(...) printf(__VA_ARGS__); fprintf(Snapshot, __VA_ARGS__);
#define CSVPRINT(...) fprintf(csvfile,__VA_ARGS__);

#define MAXSTR 500
#define MAXQUESTIONS 30
#define MAXQUESTIONSALL 60
#define MAXQUESTIONSCOOR 60 //2*30 -> MUST be twice of MAXQUESTIONS
#define SAMPLESLINETOALLOC 1000
#define SAMPLESLINE 500
#define MINSAMPLESLINE 200
#define SAMPLESLINETOPBOTTOM 300
#define MINSAMPLESLINETOPBOTTOM 100
#define ROBUSTSAMPLESLINE 1000
#define ROBUSTMINSAMPLESLINE 100
#define ROBUSTSAMPLESLINETOPBOTTOM 500
#define ROBUSTMINSAMPLESLINETOPBOTTOM 100
#define PIXELSPERPENLINE 100
#define PIXELSSEARCHSIZE 200//2*PIXELSPERPENLINE -> MUST be twice of PIXELSPERPENLINE
#define PIXELSCIRCLERADIUSHIGH 16
#define PIXELSCIRCLERADIUSLOW 10
#define PERCENTSHADED 60
#define PIXELSDIRTBLACKDOT 1 //1 black is considered dirt
#define PIXELSDIRTWHITEDOT 4 //4 white is considered dirt
#define STDDEVLOWEST 0.01
#define BARHEIGHTLOW 30
#define BARHEIGHTHIGH 80
#define ALLOWANCEMULT 3.5
#define CHEBYCHEVKVALUE 2.5
#define CHEBYCHEVKVALUEWIDTH 4
#define CHEBYCHEVKVALUEHEIGHT 4
#define CHEBYCHEVKVALUEQUES 1


typedef struct DATAXYPAIR{
    int _x;
    int _y;
}PairXY;

typedef struct DATA2BIT{
    int status; //if 0 then Empty, if 1 then points added, if 2 then allocated and ready to use
    int xlow;
    int ylow;
    int xhigh;
    int yhigh;
    int xSizeBytesAllocated;
    int ySizeBytesAllocated;
    unsigned char* buf;
}DataDigital;

typedef struct BMPIMAGE2BIT{
    int xSize;
    int ySize;
    int rasterPad;
    int setColor;
    long rasterBegin;
    long numBytesOneRow;
    FILE* filePtr;
}BmpImage;

typedef struct CHEBYCHEVCRITERION{
    double mean;
    double stddev;
}ChebyshevCriterion;

typedef struct CIRCLECRITERION{
    int radius;
    int diameter;
    int radiussquared;
}CircleCriterion;

typedef struct SLOPEANDINTERCEPT{
    double slope;
    double intercept;
}LineSlopeIntercept;

int numQuestionCol1,numQuestionCol2,numColumns;
int ColumnAnswers1 [MAXQUESTIONS];
int ColumnAnswers2 [MAXQUESTIONS];
int numOfResp;
int freqDatabase [MAXQUESTIONSALL][6];
int gddx, gddy;

void getChebyshevInt(ChebyshevCriterion* in_cc, int* arr, int num){
    int i;
    double mean=0, stddev=0;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevInt[i=%d]->(arr[i]=%d|mean=%lf)\n",i,arr[i],mean);
        mean=mean+arr[i];
    }
    mean=mean/num;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevInt[i=%d]->(arr[i]=%d|stddev=%lf)\n",i,arr[i],stddev);
        stddev=stddev+pow(arr[i]-mean,2);
    }
    stddev=stddev/num;
    stddev=sqrt(stddev);
    in_cc->mean=mean;
    in_cc->stddev=stddev;
    DBGPRINT("  FUNC:getChebyshevInt(mean=%lf|stddev=%lf)\n",in_cc->mean,in_cc->stddev);
}
void getChebyshevDouble(ChebyshevCriterion* in_cc, double* arr, int num){
    int i;
    double mean=0, stddev=0;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevDouble[i=%d]->(arr[i]=%lf|mean=%lf)\n",i,arr[i],mean);
        mean=mean+arr[i];
    }
    mean=mean/num;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevDouble[i=%d]->(arr[i]=%lf|stddev=%lf)\n",i,arr[i],stddev);
        stddev=stddev+pow(arr[i]-mean,2);
    }
    stddev=stddev/num;
    stddev=sqrt(stddev);
    in_cc->mean=mean;
    in_cc->stddev=stddev;
    DBGPRINT("  FUNC:getChebyshevDouble(mean=%lf|stddev=%lf)\n",in_cc->mean,in_cc->stddev);
}
void getChebyshevFreqIndex(ChebyshevCriterion* in_cc, int* freqarr,int* indexarr, int start, int finish){
    int i,numofitems=0;
    double mean=0, stddev=0;
    for(i=start; i<finish; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevFreqIndex[i=%d]->(indexarr[i]=%d|freqarr[i]=%d|mean=%lf)\n",i,indexarr[i],freqarr[i],mean);
        mean = mean+(indexarr[i]*freqarr[i]);
        numofitems = numofitems + freqarr[i];
    }
    mean=mean/numofitems;
    for(i=start; i<finish; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevFreqIndex[i=%d]->(indexarr[i]=%d|freqarr[i]=%d|stddev=%lf)\n",i,indexarr[i],freqarr[i],stddev);
        stddev=stddev+pow(indexarr[i]-mean,2)*freqarr[i];
    }
    stddev=stddev/numofitems;
    stddev=sqrt(stddev);
    in_cc->mean=mean;
    in_cc->stddev=stddev;
    DBGPRINT("  FUNC:getChebyshevFreqIndex(mean=%lf|stddev=%lf)\n",in_cc->mean,in_cc->stddev);
}
inline int checkIfWithinImageBounds(PairXY in_point, int xSize, int ySize){
    if(in_point._x<0 || in_point._y<0 || in_point._x>xSize || in_point._y>ySize){return 1;}
}
int G_x=-1, G_y=-1, G_value;
inline int getValue(DataDigital* indata, int x, int y){
    if(x<0 || y<0 || x>=(indata->xSizeBytesAllocated*8) || y>=(indata->ySizeBytesAllocated)){
        LOPPRINT("  FUNC:getValue(x=%d|y=%d|xalloc:%d|yalloc:%d)->ret=0  |Out of Bounds\n",x+gddx,y+gddy,indata->xSizeBytesAllocated,indata->ySizeBytesAllocated);
        return 0;
    }
    if(G_x==x>>3 && G_y==y){
        if(((G_value<<(x%8))&0x80)==0){
            LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=1  |Valid value from global cache\n",x+gddx,y+gddy,G_x,G_y,G_value);
            return 1;
        }else{
            LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=0  |Valid value from global cache\n",x+gddx,y+gddy,G_x,G_y,G_value);
            return 0;
        };
    }
    G_x=x>>3;G_y=y;
    G_value = indata->buf[G_x+(G_y*(indata->xSizeBytesAllocated))];
    if(((G_value<<(x%8))&0x80)==0){
        LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=1  |Valid value from data access\n",x+gddx,y+gddy,G_x,G_y,G_value);
        return 1;
    }else{
        LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=0  |Valid value from data access\n",x+gddx,y+gddy,G_x,G_y,G_value);
        return 0;
    };
}
inline int absValInt(int in){
    if(in<0){
        LOPPRINT("  FUNC:absValInt(%d)->ret=%d\n",in,in*-1);
        return in*-1;
    }
    LOPPRINT("  FUNC:absValInt(%d)->ret=%d\n",in,in);
    return in;
}
inline double absValDouble(double in){
    if(in<0){
        LOPPRINT("  FUNC:absValDouble(%lf)->ret=%lf\n",in,in*-1);
        return in*-1;
    }
    LOPPRINT("  FUNC:absValDouble(%lf)->ret=%lf\n",in,in);
    return in;
}
inline double getKFromChebyshev(ChebyshevCriterion cc, double in){
    if(cc.stddev<STDDEVLOWEST){
        return absValDouble((in-cc.mean)/STDDEVLOWEST);
    }
    return absValDouble((in-cc.mean)/cc.stddev);
}
inline int roundOffSignRobust(double in){
    double absDou=absValDouble(in);
    int sign;
    if(in<0){sign=-1;}else{sign=1;}
    if(absDou-(int)absDou>=0.5){absDou=absDou+1;}
    LOPPRINT("  FUNC:roundOffSignRobust(%lf)->ret=%d\n",in,(((int)absDou)*sign));
    return (((int)absDou)*sign);
}
inline int rasterRound(double in){
    if(in-(int)in>0){
        LOPPRINT("  FUNC:rasterRound(%lf)->ret=%d\n",in,(int)in+1);
        return (int)in+1;
    }
    LOPPRINT("  FUNC:rasterRound(%lf)->ret=%d\n",in,(int)in);
    return (int)in;
}
inline int roundDown(double in){
    if(in-(int)in>0){
        LOPPRINT("  FUNC:roundDown(%lf)->ret=%d\n",in,(int)in);
        return (int)in;
    }
    LOPPRINT("  FUNC:roundDown(%lf)->ret=%d\n",in,(int)in);
    return (int)in;
}
inline PairXY createXY(int x, int y){
    PairXY t1;t1._x=x;t1._y=y;return t1;
}
inline PairXY getMidpoint(PairXY P1, PairXY P2){
    PairXY outpoint;
    outpoint._x=roundOffSignRobust(((double)P1._x+P2._x)/2);
    outpoint._y=roundOffSignRobust(((double)P1._y+P2._y)/2);
    LOPPRINT("  FUNC:getMidpoint(%d,%d),(%d,%d)->(%d,%d)\n",P1._x,P1._y,P2._x,P2._y,outpoint._x,outpoint._y);
    return outpoint;
}
inline PairXY transposePoint(PairXY inpoint, int xorigin, int yorigin){
    PairXY outpoint;
    LOPPRINT("  FUNC:transposePoint(%d,%d),(%d,%d)\n",inpoint._x,inpoint._y,xorigin,yorigin);
    outpoint._x=(inpoint._x)-xorigin;
    outpoint._y=(inpoint._y)-yorigin;
    return outpoint;
}
inline LineSlopeIntercept transposeLine(LineSlopeIntercept inlsi, int slopetype, int xorigin, int yorigin){
    LineSlopeIntercept outlsi;
    outlsi.intercept = 0; outlsi.slope = 0;
    if(slopetype==0){//vertical line
        outlsi.intercept = inlsi.intercept-xorigin+(inlsi.slope*yorigin);
        outlsi.slope = inlsi.slope;
    }else if(slopetype==1){//horizontal line
        outlsi.intercept = inlsi.intercept-yorigin+(inlsi.slope*xorigin);
        outlsi.slope = inlsi.slope;
    }
    return outlsi;
}
inline PairXY findIntersection(LineSlopeIntercept verticalLine, LineSlopeIntercept horizontalLine){
    PairXY outpoint;
    outpoint._x=roundOffSignRobust(((verticalLine.slope*horizontalLine.intercept)+verticalLine.intercept)/(1-(horizontalLine.slope*verticalLine.slope)));
    outpoint._y=roundOffSignRobust(((horizontalLine.slope*verticalLine.intercept)+horizontalLine.intercept)/(1-(horizontalLine.slope*verticalLine.slope)));
    return outpoint;
}

inline assignCircleCriterion(CircleCriterion* circ, int radius){
    circ->radius=radius;
    circ->diameter=radius*2;
    circ->radiussquared=pow(radius,2);
}
inline assignMidCircleCriterion(CircleCriterion* circ, CircleCriterion* c1, CircleCriterion* c2, int type){
    int radius;
    if(type==1){radius=roundOffSignRobust(((double)c1->radius+c2->radius)/2);}
    else{radius=roundDown(((double)c1->radius+c2->radius)/2);}
    circ->radius=radius;
    circ->diameter=radius*2;
    circ->radiussquared=pow(radius,2);
}

long getImageInfo(FILE* inputFile, long offset, int numberOfChars){
    unsigned char *ptrC;
    long value=0L;
    unsigned char dummy;
    int i;

    dummy = '0'; ptrC = &dummy;

    fseek(inputFile, offset, SEEK_SET);

    for(i=1; i<=numberOfChars; i++)
    {
        fread(ptrC, sizeof(char), 1, inputFile);
        value = (long)(value + (*ptrC)*(pow(256, (i-1))));
    }

    return(value);

}

int openBmpImage(BmpImage* inBmpImage, char* sbmp){

    FILE* bmpInput = NULL;
	inBmpImage->filePtr = NULL;
    char signature[2]; /* Signature of the Image File BM = BMP */
    int nRows, nCols; /* Row and Column size of the Image */
    int xpixpeRm, ypixpeRm; /* Pixel/m */
    long nColors; /* BMP number of colors */
    long fileSize; /* BMP file size */
    long vectorSize; /* BMP's raster data in number of bytes */
    int nBits; /* # of BIts per Pixel */
    int rasterOffset; /* Beginning of the Raster Data */
    int setColor;
    int nRasterPad;
    int i;

    if ((bmpInput = fopen(sbmp, "r+b")) == NULL)
    {
        INFPRINT("ERROR: Cannot read BMP file. File exit.\n");
        return 1;
    } /* Read BMP input FILE* /

    fseek(bmpInput, 0L, SEEK_SET); /* File pointer at byte #0 */

    /* Signature of the File BM = BMP at byte # 0*/
    for(i=0; i<2; i++)
    {
        signature[i] = (char)getImageInfo(bmpInput, (long)i, 1);
    }
    if ((signature[0] == 'B') && (signature[1] == 'M')) {
        DBGPRINT("It is verified that the Image is in Bitmap format\n");
    }else
    {
        INFPRINT("ERROR: The image is not in bitmap format. File exit.\n");
        return 2;
    }

    /* Read BMP bits/pixel at byte #28 */
    nBits = (int)getImageInfo(bmpInput, 28, 2);
    DBGPRINT("The Image is \t%d-bit\n", nBits);

    if(nBits!=1){
        INFPRINT("ERROR: The Image is not a 1-bit Bitmap. Pls resave this bitmap. File exit.\n");
        return 3;
    }
    /* Position of First Raster Data at byte # 10*/
    rasterOffset = (int)getImageInfo(bmpInput, 10, 4);
    inBmpImage->rasterBegin = rasterOffset;
    DBGPRINT("The beginning of the Raster Data \nis at \t\t%d byte\n", rasterOffset);

    /* Read BMP file size at byte # 2 */
    fileSize = getImageInfo(bmpInput, 2, 4);
    DBGPRINT("File size is \t%ld byte\n", fileSize);

    /* Read BMP width at byte #18 */
    nCols = (int)getImageInfo(bmpInput, 18, 4);
    DBGPRINT("Width: \t\t%d\n", nCols);
    inBmpImage->xSize=nCols;

    /* Read BMP height at byte #22 */
    nRows = (int)getImageInfo(bmpInput, 22, 4);
    DBGPRINT("Height: \t%d\n", nRows);
    inBmpImage->ySize=nRows;
    /* # of Pixels in a meter in x direction at byte # 38 */
    xpixpeRm = (int)getImageInfo(bmpInput, 38, 4);
    DBGPRINT("Image has \t%d pixels per m in x-dir.\n", xpixpeRm);

    /* # of Pixels in a meter in y direction at byte # 42 */
    ypixpeRm = getImageInfo(bmpInput, 42, 4);
    DBGPRINT("Image has \t%d pixels per m in y-dir.\n", ypixpeRm);

    nRasterPad=( 4-(rasterRound((double)nCols/8)%4) ) % 4;
    inBmpImage->rasterPad = nRasterPad;
    DBGPRINT("Raster pad is %d.\n", nRasterPad);

    /* Read number of colors at byte #46 */
    nColors = pow(2L,nBits);
    DBGPRINT("There are \t%ld number of Colors \n", nColors);

    vectorSize = (long)((long)nCols*(long)nRows);
    DBGPRINT("Vector Size is \t%ld\n", vectorSize);

    setColor = (int)getImageInfo(bmpInput, 54, 1);

    if(setColor==0xFF){
        DBGPRINT("Setcolor is White\n");
        setColor=0;
    }else{
        DBGPRINT("Setcolor is Black\n");
        setColor=1;
    }
    inBmpImage->setColor = setColor;

    inBmpImage->numBytesOneRow = rasterRound((double)nCols/8) + nRasterPad;
    DBGPRINT("Number of bytes for one row is \t%ld\n", inBmpImage->numBytesOneRow);

    inBmpImage->filePtr=bmpInput;
    return 0;
} /* end of main */

inline void closeBmpImage(BmpImage* inBmpImage){
    if(inBmpImage->filePtr!=NULL){
        fclose(inBmpImage->filePtr);
    }
    inBmpImage->filePtr = NULL;
}

int getDataFromBmp(BmpImage* inBmpImage,DataDigital* indata){
    if(indata->status!=2){return 1;}
    unsigned char *ptrC;
    int x, xsizebytes=indata->xSizeBytesAllocated;
    int y, ylow=indata->ylow, yhigh=indata->yhigh;
    int ysize=inBmpImage->ySize, nbor = inBmpImage->numBytesOneRow;
    int rasterBegin = inBmpImage->rasterBegin;
    FILE* t1fileaddress = inBmpImage->filePtr;
    long offset;
    int i;
    DBGPRINT("  FUNC:getDataFromBmp(LOW(%d,%d) to HIGH(%d,%d))  |Transferring data from BMP to DataDigital.\n", indata->xlow,indata->ylow,indata->xhigh,indata->yhigh);

    if(inBmpImage->setColor==1){
        x=indata->xlow/8;
        for(y=ylow; y<=yhigh; y++){
            offset = rasterBegin+(nbor*(ysize-y-1))+x;
            ptrC = &(indata->buf[(y-ylow)*xsizebytes]);
            fseek(t1fileaddress, offset, SEEK_SET);
            LOPPRINT("  FUNCLOOP:getDataFromBmp[x=%d|y=%d]->(offset=%d|nbor=%d)\n",x,y,offset,nbor);
            fread(ptrC, sizeof(char), xsizebytes, t1fileaddress);
        }
    }else{
        x=indata->xlow/8;
        for(y=ylow; y<=yhigh; y++){
            offset = rasterBegin+(nbor*(ysize-y-1))+x;
            ptrC = &(indata->buf[(y-ylow)*xsizebytes]);
            fseek(t1fileaddress, offset, SEEK_SET);
            LOPPRINT("  FUNCLOOP:getDataFromBmp[x=%d|y=%d]->(offset=%d|nbor=%d)\n",x,y,offset,nbor);
            fread(ptrC, sizeof(char), xsizebytes, t1fileaddress);
            for(i=0; i<xsizebytes; i++){ptrC[i]=(ptrC[i])^(0xFF);}
        }
    }
    DBGPRINT("  FUNCOUT:getDataFromBmp(LOW(%d,%d) to HIGH(%d,%d))  |Transferred data from BMP to DataDigital.\n", indata->xlow,indata->ylow,indata->xhigh,indata->yhigh);
    indata->status=3;
#ifdef  DBGFLAG
    gddx=indata->xlow;
    gddy=indata->ylow;
    DBGPRINT("  FUNCOUT:getDataFromBmp[gddx=%d|gddy=%d]\n",gddx,gddy);
#endif
    return 0;
}
inline int allocData(DataDigital* indata){
    if(indata->status!=1){return 1;}
    indata->xSizeBytesAllocated=(indata->xhigh-indata->xlow+1)/8;
    indata->ySizeBytesAllocated=(indata->yhigh-indata->ylow)+1;
    indata->buf = (unsigned char*)malloc((indata->xSizeBytesAllocated)*(indata->ySizeBytesAllocated)*sizeof(char));
    if(indata->buf==NULL){return 1;}
    indata->status=2;
    return 0;
}
inline void deAllocData(DataDigital* indata){
    if(indata->status<2){return;}
    if(indata->buf!=NULL){free(indata->buf);}
    indata->buf = NULL;
    indata->xSizeBytesAllocated=0;indata->ySizeBytesAllocated=0;
    indata->status=0;
}
inline void cleanDataDigital(DataDigital* indata){
    if(indata->buf!=NULL){free(indata->buf);}
    indata->buf = NULL;
    indata->xSizeBytesAllocated=0;indata->ySizeBytesAllocated=0;
    indata->status=0;
}

inline void printDataDigitalBuffer(DataDigital* indata){
    if(indata->status!=3){return;}
#ifdef  DBGFLAG
    FILE* bufferprint = NULL;
    if ((bufferprint = fopen("BUFFERTEST.TXT", "w")) == NULL){
        INFPRINT("ERROR: Cannot write to BUFFER.TXT. File exit.\n");
        return;
    }
    int x, y, m;
    unsigned char tbuf;
    for(y=0;y<indata->ySizeBytesAllocated;y++){
        for(x=0;x<indata->xSizeBytesAllocated;x++){
            tbuf = indata->buf[(y*indata->xSizeBytesAllocated)+x];
            for(m=0;m<8;m++){
                if((tbuf&0x80)==0x80){fprintf(bufferprint,"_");
                }else{fprintf(bufferprint,"X");
                }
                tbuf = tbuf<<1;
            }
        }
        fprintf(bufferprint,"\n");
    }
    fclose(bufferprint);
    bufferprint=NULL;
#endif
}
inline void printDataDigitalProperty(DataDigital* indata){
    DBGPRINT("\n");
    if(indata->status==0){INFPRINT("DDINFO: DataDigital Status: IDLE\n");
    }else if(indata->status==1){INFPRINT("DDINFO: DataDigital Status: POINTS ADDED\n");
    }else if(indata->status==2){INFPRINT("DDINFO: DataDigital Status: ALLOCATED\n");
    }else if(indata->status==3){INFPRINT("DDINFO: DataDigital Status: DATA TRANSFERRED, Ready To Use\n");
    }
    INFPRINT("DDINFO: DataDigital Status: Lowest: (%d,%d) ", indata->xlow,indata->ylow);
    INFPRINT("DDINFO: Highest: (%d,%d) \n", indata->xhigh,indata->yhigh);
    INFPRINT("DDINFO: SizeAllocated: (%d,%d) ", indata->xSizeBytesAllocated,indata->ySizeBytesAllocated);
    INFPRINT("DDINFO: Address: %X \n", indata->buf);
    DBGPRINT("\n");
}
void addPointToDataDigital(BmpImage* inBmpImage,DataDigital* indata, int xp, int yp){
    DBGPRINT("  FUNC:addPointToDataDigital(xp=%d|yp=%d|xsize=%d|ysize=%d)\n",xp,yp,inBmpImage->xSize,inBmpImage->ySize);
    if(xp<0){xp=0;}
    if(yp<0){yp=0;}
    if(xp>=inBmpImage->xSize){xp=inBmpImage->xSize-1;}
    if(yp>=inBmpImage->ySize){yp=inBmpImage->ySize-1;}


    if(indata->status==0){
        indata->xlow=(xp>>3)<<3;indata->xhigh=(((xp>>3)+1)<<3)-1;
        indata->ylow=yp;indata->yhigh=yp;
        indata->status=1;
        DBGPRINT("  FUNC:addPointToDataDigital(status=%d)  |First Point\n",indata->status);
        return;
    }
    if(xp<indata->xlow){indata->xlow=(xp>>3)<<3;
    }else if(xp>indata->xhigh){indata->xhigh = (((xp>>3)+1)<<3)-1;//=(xrem>0) ? xp+8-xrem : xp;
    }
    if(yp<indata->ylow){indata->ylow=yp;
    }else if(yp>indata->yhigh){indata->yhigh=yp;
    }
    DBGPRINT("  FUNC:addPointToDataDigital(LOW(%d,%d) to HIGH(%d,%d))\n", indata->xlow,indata->ylow,indata->xhigh,indata->yhigh);
}

inline double checkIfShaded(DataDigital* indata,PairXY center, CircleCriterion circ, int ques, int col, int choice, PairXY point1, PairXY point2){
    int startx,starty,incx,incy,diameter;
    int countall,countblack;
    int noChange,type,moved;
    double scorePercent,maxScorePercent;
#ifdef CIRFLAG
    char tempstr[MAXSTR];
    sprintf(tempstr,"CIR_COL%d_QUES%d_R%d_choice%d.txt",col,ques,circ.radius,choice);
	circlefile=NULL;
    if ((circlefile = fopen(tempstr, "w")) == NULL){
        INFPRINT("ERROR: Error in circle log file.\n"); return 1;
    }
#endif
    noChange=0;
    type=0; moved=0;
    scorePercent=0; maxScorePercent=0;
    while(noChange!=0x1111){
        if(type>=5){type=1;noChange=0;}
        if(type==1){ center._x=center._x+1;
        }else if(type==2){ center._y=center._y+1;
        }else if(type==3){ center._y=center._y-1;
        }else if(type==4){ center._x=center._x-1;
        }
        startx = center._x-circ.radius;
        starty = center._y-circ.radius;
        diameter = circ.diameter;
        countall=0;countblack=0;
        for(incy=0;incy<=diameter;incy++){
            for(incx=0;incx<=diameter;incx++){
                if(pow(incx-circ.radius,2)+pow(incy-circ.radius,2)<=circ.radiussquared){
                    countall++;
                    if(getValue(indata,startx+incx,starty+incy)){
                        countblack++;CIRPRINT("X");
                    }else{CIRPRINT("-");}
                }else{CIRPRINT("_");}
            }CIRPRINT("\n");
        }
        scorePercent = (double)countblack/countall*100;
        if(type==0){maxScorePercent=scorePercent;}
        if(maxScorePercent<scorePercent){
            moved=1;
        }else{
            if(type==1){ center._x=center._x-1;
            }else if(type==2){ center._y=center._y-1;
            }else if(type==3){ center._y=center._y+1;
            }else if(type==4){ center._x=center._x+1;
            }
        }
        if(moved==0){
            if(type==1){ noChange=noChange|0x0001;
            }else if(type==2){ noChange=noChange|0x0010;
            }else if(type==3){ noChange=noChange|0x0100;
            }else if(type==4){ noChange=noChange|0x1000;
            }
        }
        CIRPRINT("CircleCenter:(%d,%d)\n",center._x+gddx,center._y+gddy);
        CIRPRINT("PointLeft:(%d,%d) PointRight:(%d,%d)\n",point1._x+gddx,point1._y+gddy,point2._x+gddx,point2._y+gddy);
        CIRPRINT("[type:%d|noChange:%4X|moved:%d]->[ScorePercent=%lf | maxScorePercent=%lf]\n",type,noChange,moved,scorePercent,maxScorePercent);
        if(maxScorePercent<scorePercent){
            maxScorePercent=scorePercent;
        }else{
            moved=0;
            type++;
        }
        if(maxScorePercent>=PERCENTSHADED){break;}
    }
#ifdef CIRFLAG
    fclose(circlefile);
#endif
    DBGPRINT("  FUNC:checkIfShaded out=%3.2lf\n",((double)countblack/countall*100));
    return maxScorePercent;
}
inline int processOneQuestion(DataDigital* indata, PairXY point1, PairXY point2, int ques, int col, CircleCriterion circ){
    DBGPRINT("  FUNC:processOneQuestion point1(%d,%d) point2(%d,%d)\n",point1._x+gddx,point1._y+gddy,point2._x+gddx,point2._y+gddy);
    PairXY temppoint;
    int t1,tch;
    double dtemp;
    tch=0;
#ifdef CIRFLAG
    char tempstr[MAXSTR];
    FILE* circlefile = NULL;
    sprintf(tempstr,"CIR_COL%d_QUES%d.txt",col,ques);
    if ((circlefile = fopen(tempstr, "w")) == NULL){
        INFPRINT("ERROR: Error in circle log file.\n"); return 1;
    }
#endif
    for(t1=0;t1<5;t1++){
        dtemp = (((double)t1*2)+1)/10;
        CIRPRINT("DTEMP:%lf (%d + %d)\n",dtemp,point1._x+gddx,roundOffSignRobust(((double)point2._x-point1._x)*dtemp));
        CIRPRINT("POINT1:(%d,%d)\n",point1._x+gddx,point1._y+gddy);
        CIRPRINT("POINT2:(%d,%d)\n",point2._x+gddx,point2._y+gddy);
        temppoint._x = point1._x+ roundOffSignRobust(((double)point2._x-point1._x)*dtemp);
        temppoint._y = point1._y+ roundOffSignRobust(((double)point2._y-point1._y)*dtemp);
        CIRPRINT("TPOINT:(%d,%d)\n",temppoint._x+gddx,temppoint._y+gddy);
        dtemp = checkIfShaded(indata,temppoint,circ,ques,col,5-t1, point1, point2);
        LOPPRINT("  FUNCLOOP:processOneQuestion (x=%d,y=%d,t1=%d)->%lf\n",temppoint._x+gddx,temppoint._y+gddy,t1,dtemp);
        if(dtemp>PERCENTSHADED){
            if(tch==0){
                tch=5-t1;
            }else{
                INFPRINT("WARN: Multiple answers in ques#=%d column=%d r=%d. Answers: %d and %d\n",ques,col,circ.radius,tch,5-t1);
                return 6;
            }
        }
    }
#ifdef CIRFLAG
    fclose(circlefile);
#endif
    if(tch!=0){
        return tch;
    }else{
        INFPRINT("WARN: No answer in ques#=%d column=%d r=%d.\n",ques,col,circ.radius);
        return 0;
    }
}
int processOneColumn(DataDigital* indata, PairXY* QuesArr1, PairXY* QuesArr2, int numQuestionsColumn, int columnNumber){
    int t1, t2, iteration, tchoice;
    PairXY point1, point2;
    int xlow=indata->xlow, ylow=indata->ylow;
    CircleCriterion circhighest, circlowest, clow, chigh, currentcirc;
    assignCircleCriterion(&circhighest,PIXELSCIRCLERADIUSHIGH);
    assignCircleCriterion(&circlowest,PIXELSCIRCLERADIUSLOW);
    assignMidCircleCriterion(&currentcirc,&circlowest,&circhighest,1);

    t2=0;
    DBGPRINT("  FUNC:processOneColumn low(x=%d,y=%d)\n",indata->xlow,indata->ylow);
    tchoice=0;
    for(t1=0;t1<numQuestionsColumn;t1++){
        point1 = getMidpoint(QuesArr1[t2],QuesArr1[t2+1]);
        point2 = getMidpoint(QuesArr2[t2],QuesArr2[t2+1]);
        LOPPRINT("  FUNCLOOP:processOneColumn point1(x=%d,y=%d) point1(x=%d,y=%d)\n",point1._x,point1._y,point2._x,point2._y);
        point1 = transposePoint(point1,xlow,ylow);
        point2 = transposePoint(point2,xlow,ylow);
        clow=circlowest; chigh=circhighest;
        iteration=0;
        do{
            tchoice = processOneQuestion(indata, point1, point2, t1+1, columnNumber,currentcirc);
            LOPPRINT("  FUNCLOOPX:processOneColumn tchoice=%d r=%d\n",tchoice,currentcirc.radius);
            if(tchoice==0){
                chigh=currentcirc;
                assignMidCircleCriterion(&currentcirc,&clow,&chigh,0);
                LOPPRINT("INFO:Retrying with more lenient parameters-> ques#=%d r=%d\n",t1+1,currentcirc.radius);
            }else if(tchoice==6){
                clow=currentcirc;
                assignMidCircleCriterion(&currentcirc,&clow,&chigh,1);
                LOPPRINT("INFO:Retrying with more strict parameters-> ques#=%d r=%d\n",t1+1,currentcirc.radius);
            }else{iteration=-1;
                break;
            }
            iteration++;
        }while (currentcirc.radius!=circlowest.radius && currentcirc.radius!=circhighest.radius && iteration<5);
        if(iteration!=-1){
            INFPRINT("ERROR: Error in question number=%d column=%d r=%d\n",t1+1,columnNumber,currentcirc.radius);
            //return 1;
        }
        INFPRINT("Question number=%d column=%d -> choice=%d r=%d\n",t1+1,columnNumber,tchoice,currentcirc.radius);
        if(columnNumber==1){
            if(tchoice>=1 && tchoice<=5){ColumnAnswers1[t1]=tchoice;}
            else{ColumnAnswers1[t1]=0;}
        }else if(columnNumber==2){
            if(tchoice>=1 && tchoice<=5){ColumnAnswers2[t1]=tchoice;}
            else{ColumnAnswers2[t1]=0;}
        }
        t2=t2+2;
    }
    return 0;
}

inline int followLineGetLengthX(DataDigital* indata,PairXY start, PairXY p1){
    //p2 and p3 are opposite directions, use states to dont go backwards
    int state,x,y,pty;
    LOPPRINT("  FUNC:followLineGetLengthX Start(%d|%d) P1(%d|%d) P3(%d|%d)\n",start._x+gddx,start._y+gddy,p1._x+gddx,p1._y+gddy);
    x=start._x; y=start._y; pty=0; state=0;
    while(1){
        LOPPRINT("  FUNCLOOP:followLineGetLengthX(x=%d|y=%d|pt=%d)\n",x+gddx,y+gddy,pty);
        if(pty>=PIXELSPERPENLINE){break;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(pty=%d) |Perpendicular line exit\n",pty);
        }else if(getValue(indata,x+p1._x,y+p1._y)==1){x=x+p1._x; y=y+p1._y; state = 1; pty=pty+1;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Follow P1:(%d,%d)\n",x+gddx,y+gddy);
        }else if(state==1){while(getValue(indata,x,y-1)==1){y=y-1;} state=2;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Find TOP:(%d,%d)\n",x+gddx,y+gddy);
        }else if(state==2 && getValue(indata,x,y+1)==1){y=y+1;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Go Down(%d,%d)\n",x+gddx,y+gddy);
        }else{ break;
        }
    }
    LOPPRINT("  FUNC:followLineGetLengthX->(out=%d)\n",pty);
    return pty;
}

int findLineImageFromLeft(PairXY* in_line, int numsamplesize, unsigned char* in_buf,int xsizebytesallocated,PairXY inStart,PairXY inEnd){
    int xt,yt,lt,mt,pt,ptwhite,lt_success;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromLeft(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        LOPPRINT("  FUNCLOOP:findLineImageFromLeft[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        yt = in_line[lt_success]._y*xsizebytesallocated;
        pt = 0;
        ptwhite=0;
        mt=in_line[lt_success]._x%8;
        for(xt=in_line[lt_success]._x/8;xt<xsizebytesallocated;xt++){//linebyteloop
            dummy = in_buf[yt+xt];
            for(;mt<8;mt++){//linebitloop
                mask=0x80>>mt;
                LOPPRINT("  FUNCLOOPXXX:findLineImageFromLeft[x=%d|y=%d|mt=%d|pt=%d]->dummy=%X|mask%X|bit=%d\n",(xt*8)+mt+gddx,in_line[lt_success]._y+gddy,mt,pt,dummy,mask,(dummy&mask)==0x00);
                if(pt>=PIXELSPERPENLINE){xt=xsizebytesallocated;break;}
                if((dummy&mask)==0x00){//black
                    pt=pt+1;
                    ptwhite=0;
                }else if(pt>PIXELSDIRTBLACKDOT && ptwhite>=PIXELSDIRTWHITEDOT){
                    pt=pt-ptwhite;
                    in_line[lt_success]._x = roundOffSignRobust( (xt*8)+mt-1-pt+(((double)pt)/2)-ptwhite );//minus-1 to get last white
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromLeft Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    xt=xsizebytesallocated;
                    lt_success++;
                    break;
                }else{
                    if(ptwhite<PIXELSDIRTWHITEDOT && pt>0){//consider white dirt
                        ptwhite++;
                        pt++;
                    }else{
                        pt=0;//if dirt encountered clear once white again
                    }
                }
            }
            mt=0;
        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromLeft[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;

}

int findLineImageFromRight(PairXY* in_line, int numsamplesize, unsigned char* in_buf,int xsizebytesallocated,PairXY inStart,PairXY inEnd){
    int xt,yt,lt,mt,pt,ptwhite,lt_success;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromRight(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        yt = in_line[lt_success]._y*xsizebytesallocated;
        pt = 0;
        ptwhite=0;
        mt=in_line[lt_success]._x%8;
        LOPPRINT("  FUNCLOOP:findLineImageFromRight[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        for(xt=in_line[lt_success]._x/8;xt>=0;xt--){//linebyteloop
            dummy = in_buf[yt+xt];
            for(;mt>=0;mt--){//linebitloop
                mask=0x80>>mt;
                LOPPRINT("  FUNCLOOPXXX:findLineImageFromRight[x=%d|y=%d|mt=%d|pt=%d]->bit=%d\n",(xt*8)+mt+gddx,in_line[lt_success]._y+gddy,mt,pt,(dummy&mask)==0x00);
                if(pt>=PIXELSPERPENLINE){xt=-1;break;}
                if((dummy&mask)==0x00){//black
                    pt=pt+1;
                    ptwhite=0;
                }else if(pt>PIXELSDIRTBLACKDOT && ptwhite>=PIXELSDIRTWHITEDOT){
                    pt=pt-ptwhite;
                    in_line[lt_success]._x =roundOffSignRobust( (xt*8)+mt+(((double)pt)/2)+ptwhite );
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromRight Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    xt=-1;
                    lt_success++;
                    break;
                }else{
                    if(ptwhite<PIXELSDIRTWHITEDOT && pt>0){//consider white dirt
                        ptwhite++;
                        pt++;
                    }else{
                        pt=0;//if dirt encountered clear once white again
                    }
                }
            }
            mt=7;
        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromRight[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;
}

int findLineImageFromTop(DataDigital* indata, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd){
    int xt,yt,lt,lt_success,pt,iy,pty;
    int xsizebytesallocated, ysizebytesallocated;
    xsizebytesallocated = indata->xSizeBytesAllocated;
    ysizebytesallocated = indata->ySizeBytesAllocated;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromTop(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        xt = in_line[lt_success]._x/8;
        mask=0x80>>(in_line[lt_success]._x%8);
        pt = 0;
        LOPPRINT("  FUNCLOOP:findLineImageFromTop[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        for(iy=in_line[lt_success]._y; iy<ysizebytesallocated; iy++){//linebyteloop
            yt=(iy*xsizebytesallocated);
            dummy = indata->buf[yt+xt];
            LOPPRINT("  FUNCLOOPXXX:findLineImageFromTop[x=%d,y=%d|pt=%d|dummy=%d|mask=%d]->bit=%d\n",in_line[lt_success]._x+gddx,iy+gddy,pt,dummy,mask,(dummy&mask)==0x00);
            if(pt>=PIXELSPERPENLINE){break;}
            if((dummy&mask)==0x00){//black
                    pt=pt+1;
            }else if(pt>PIXELSDIRTBLACKDOT){
                in_line[lt_success]._y = roundOffSignRobust( iy-1-pt+(((double)pt)/2) );//minus-1 to get last white
                pty=1+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(1,0) );
                pty=pty+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(-1,0) );
                if(pty>=PIXELSPERPENLINE){
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromTop Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    lt_success++;
                    break;
                }else{
                    pt=0;
                }
            }else{
                pt=0;//if dirt encountered clear once white again
            }

        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromTop[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;
}

int findLineImageFromBottom(DataDigital* indata, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd){
    int xt,yt,lt,lt_success,pt,iy,pty;
    int xsizebytesallocated, ysizebytesallocated;
    xsizebytesallocated = indata->xSizeBytesAllocated;
    ysizebytesallocated = indata->ySizeBytesAllocated;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromBottom(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        xt = in_line[lt_success]._x/8;
        mask=0x80>>(in_line[lt_success]._x%8);
        pt = 0;
        LOPPRINT("  FUNCLOOP:findLineImageFromBottom[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        for(iy=in_line[lt_success]._y; iy>=0; iy--){//linebyteloop
            yt=(iy*xsizebytesallocated);
            dummy = indata->buf[yt+xt];
            LOPPRINT("  FUNCLOOPXXX:findLineImageFromBottom[x=%d,y=%d|pt=%d|dummy=%d|mask=%d]->bit=%d\n",in_line[lt_success]._x+gddx,iy+gddy,pt,dummy,mask,(dummy&mask)==0x00);
            if(pt>=PIXELSPERPENLINE){break;}
            if((dummy&mask)==0x00){//black
                pt=pt+1;
            }else if(pt>PIXELSDIRTBLACKDOT){
                in_line[lt_success]._y = roundOffSignRobust( iy+(((double)pt)/2) );//minus-1 to get last white
                pty=1+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(1,0) );
                pty=pty+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(-1,0) );
                if(pty>=PIXELSPERPENLINE){
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromBottom Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    lt_success++;
                    break;
                }else{
                    pt=0;
                }
            }else {
                pt=0;//if dirt encountered clear once white again
            }

        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromBottom[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;
}

inline int getSlope(PairXY* in_samples,double* out_slope, int nsize, int type){//type=0 is yline, type=1 is xline
    int i;
    if(type==0){
        for(i=1;i<nsize;i++){
            if(in_samples[i]._y==in_samples[i-1]._y){return 1;}
            out_slope[i-1]=((double)in_samples[i]._x-in_samples[i-1]._x)/((double)in_samples[i]._y-in_samples[i-1]._y);
            LOPPRINT("  FUNCLOOP:getSlope(%d)[ x[i]=%d|y[i]=%d|x[i-1]=%d|y[i-1]=%d ]->slope=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,in_samples[i-1]._x+gddx,in_samples[i-1]._y+gddy,out_slope[i-1]);
        }
    }else if(type==1){
        for(i=1;i<nsize;i++){
            if(in_samples[i]._x==in_samples[i-1]._x){return 1;}
            out_slope[i-1]=((double)in_samples[i]._y-in_samples[i-1]._y)/((double)in_samples[i]._x-in_samples[i-1]._x);
            LOPPRINT("  FUNCLOOP:getSlope(%d)[ x[i]=%d|y[i]=%d|x[i-1]=%d|y[i-1]=%d ]->slope=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,in_samples[i-1]._x+gddx,in_samples[i-1]._y+gddy,out_slope[i-1]);
        }
    }else{
        return 1;
    }
    return 0;
}
inline double getBarHeight(PairXY point1,PairXY point2){
    double barHeight;
    barHeight=pow((double)point1._x-point2._x,2) + pow((double)point1._y-point2._y,2);
    barHeight=sqrt(barHeight);
    return barHeight;
}
inline void getBarHeightArr(PairXY* questionsCoor,double* barHeight, int nsize){
    int i,j;
    for(i=0;i<nsize;i=i+2){
        j=i/2;
        barHeight[j]=getBarHeight(questionsCoor[i+1],questionsCoor[i]);
        LOPPRINT("  FUNCLOOP:getBarHeightArr(j=%d|barHeight=%lf) [%d]->(%ld|%ld) [%d]->(%ld|%ld)\n",j,barHeight[j],i,questionsCoor[i]._x+gddx,questionsCoor[i]._y+gddy,i+1,questionsCoor[i+1]._x+gddx,questionsCoor[i+1]._y+gddy);
    }
}
inline double getIntercept(PairXY* in_samples,double slope, int nsize, int type){
    int i;
    double intercept=0;
    DBGPRINT("  FUNC:getIntercept(slope=%lf)\n",slope);
    if(type==0){
        for(i=0;i<nsize;i++){
            LOPPRINT("  FUNCLOOP:getIntercept(%d)[x[i]=%d|y[i]=%d]->xintercept=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,intercept);
            intercept=intercept+in_samples[i]._x-(slope*in_samples[i]._y);
        }
        intercept=intercept/nsize;
        DBGPRINT("  FUNC:getIntercept->ret=%lf  |xIntercept\n",intercept+gddx);
    }else if(type==1){
        for(i=0;i<nsize;i++){
            LOPPRINT("  FUNCLOOP:getIntercept(%d)[x[i]=%d|y[i]=%d]->yintercept=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,intercept);
            intercept=intercept+in_samples[i]._y-(slope*in_samples[i]._x);
        }
        intercept=intercept/nsize;
        DBGPRINT("  FUNC:getIntercept->ret=%lf  |yIntercept\n",intercept+gddx);
    }
    return intercept;
}
int removeOutliersFromLine(PairXY* lineSamples, double* invslope, ChebyshevCriterion* chebycriterion, int numLineSamples, int type){
    int t1,t2;
    int* scoretoremove=NULL;
	scoretoremove = (int*)malloc(numLineSamples*sizeof(int));
	if(scoretoremove==NULL){return 0;}
    ChebyshevCriterion cc;
    t2=numLineSamples;
    do{
        //Remove Outliers
        numLineSamples=t2;
        getSlope(lineSamples,invslope,numLineSamples,type);
        getChebyshevDouble(&cc, invslope, numLineSamples-1);
        DBGPRINT("  FUNC:removeOutliersFromLine(slopeMean=%lf|slopeStdDev=%lf)\n",cc.mean,cc.stddev);
        for(t1=0;t1<numLineSamples;t1++){scoretoremove[t1]=0;}//clear array
        for(t1=0;t1<numLineSamples-1;t1++){
            LOPPRINT("  FUNCLOOP:removeOutliersFromLine[t1=%d|(x=%d,y=%d)]->slopeMean:%lf, deviate(k):%lf\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy,invslope[t1],getKFromChebyshev(cc,invslope[t1]));
            if(getKFromChebyshev(cc,invslope[t1])>CHEBYCHEVKVALUE){
                scoretoremove[t1]=1;scoretoremove[t1+1]=1;
                LOPPRINT("  FUNCLOOP:removeOutliersFromLine[t1=%d|(x=%d,y=%d)]->deviate(k)=%lf |  delete this, too much deviation\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy,getKFromChebyshev(cc,invslope[t1]));
                LOPPRINT("  FUNCLOOP:removeOutliersFromLine[t1=%d|(x=%d,y=%d)] |  delete this too, too much deviation\n",t1+1,lineSamples[t1+1]._x+gddx,lineSamples[t1+1]._y+gddy);
            }
        }
        t2=0;
        for(t1=0;t1<numLineSamples;t1++){
            if(scoretoremove[t1]==0){
                LOPPRINT("  FUNCLOOP:removeOutliersFromLine(SuccessfulLineSamples)-> (t2=%d|(x=%d|y=%d))\n",t2,lineSamples[t2]._x+gddx,lineSamples[t2]._y+gddy);
                lineSamples[t2]=lineSamples[t1]; t2++;
            }
        }
    }while(t2!=numLineSamples);
    *chebycriterion = cc;
#ifdef DBGFLAG
    for(t1=0;t1<numLineSamples;t1++){//lineSamples
        DBGPRINT("  FUNCOUT:removeOutliersFromLine[%d]->[x=%d|y=%d]\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy);
    }
#endif
	free(scoretoremove);
	scoretoremove=NULL;
    return numLineSamples;
}
int removeOutliersFromLineSmart(PairXY* lineSamples, int numLineSamples, int numLineSamplesDesired, int type){
    int t1, t1max;
    double maxDistance,tempDistance;
    double total_x, total_y, total_xy, total_x2, m_least_squares, b_least_squares;
    for(; numLineSamplesDesired<numLineSamples; numLineSamples--){//Remove Outliers
        //linear regression
        total_x=0; total_y=0; total_xy=0; total_x2=0;
        for(t1=0;t1<numLineSamples;t1++){
            if(type==0){
                total_x = total_x+lineSamples[t1]._y;
                total_y = total_y+lineSamples[t1]._x;
                total_xy = total_xy+(lineSamples[t1]._x*lineSamples[t1]._y);
                total_x2 = total_x2+(lineSamples[t1]._y*lineSamples[t1]._y);
            }else{
                total_x = total_x+lineSamples[t1]._x;
                total_y = total_y+lineSamples[t1]._y;
                total_xy = total_xy+(lineSamples[t1]._x*lineSamples[t1]._y);
                total_x2 = total_x2+(lineSamples[t1]._x*lineSamples[t1]._x);
            }
        }
        m_least_squares = ((total_xy*numLineSamples)-(total_x*total_y))/((total_x2*numLineSamples)-(total_x*total_x));
        b_least_squares = (total_y/numLineSamples)-((total_x/numLineSamples)*m_least_squares);

        DBGPRINT("  FUNC:removeOutliersFromLineSmart(slope(m_least_squares)=%lf | intercept(b_least_squares)=%lf)\n",m_least_squares,b_least_squares);
        maxDistance=0;
        t1max=0;
        for(t1=0;t1<numLineSamples;t1++){
            if(type==0){
                tempDistance = absValDouble((m_least_squares*lineSamples[t1]._y)+b_least_squares-lineSamples[t1]._x);
            }else{
                tempDistance = absValDouble((m_least_squares*lineSamples[t1]._x)+b_least_squares-lineSamples[t1]._y);
            }
            LOPPRINT("  FUNCLOOP:removeOutliersFromLineSmart[t1=%d|(x=%d,y=%d)]->slope:%lf, intercept:%lf, tempDistance:%lf, maxDistance:%lf\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy,m_least_squares,b_least_squares,tempDistance,maxDistance);
            if(tempDistance > maxDistance){
                //DBGPRINT("  FUNC:removeOutliersFromLineSmart MAXCHANGE[t1=%d|(x=%d,y=%d)]->tempDistance=%lf\n",t1max,lineSamples[t1max]._x+gddx,lineSamples[t1max]._y+gddy,tempDistance);
                maxDistance = tempDistance;
                t1max=t1;
            }
        }
        DBGPRINT("  FUNC:removeOutliersFromLineSmart REMOVED[t1=%d|(x=%d,y=%d)]->maxDistance=%lf\n",t1max,lineSamples[t1max]._x+gddx,lineSamples[t1max]._y+gddy,maxDistance);
        for(t1=t1max;t1+1<numLineSamples;t1++){
            lineSamples[t1]=lineSamples[t1+1];
        }
    }
#ifdef DBGFLAG
    for(t1=0;t1<numLineSamples;t1++){//lineSamples
        DBGPRINT("  FUNCOUT:removeOutliersFromLineSmart[%d]->[x=%d|y=%d]\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy);
    }
#endif
    return numLineSamples;
}
void getQFindSamples(PairXY* qFindSamples, int numQFindSamples, PairXY start, PairXY finish, LineSlopeIntercept lsi, int barheightsamplepixels){
    int t1,ytemp;
    qFindSamples[0]=start;
    ytemp=start._y;
    DBGPRINT("  FUNC:getQFindSamples start(%d|%d) finish(%d|%d)\n",start._x+gddx,start._y+gddy,finish._x+gddx,finish._y+gddy);
    DBGPRINT("  FUNC:getQFindSamples start(%d|%d) |  start with startSample\n",start._x+gddx,start._y+gddy);
    for(t1=1;t1<numQFindSamples-1;t1++){
        ytemp=ytemp+barheightsamplepixels;
        qFindSamples[t1]._y=ytemp;
        qFindSamples[t1]._x=roundOffSignRobust((((double)ytemp)*lsi.slope)+lsi.intercept);
        LOPPRINT("  FUNCLOOP:getQFindSamples [t1=%d]->(quesx=%d,quesy=%d)\n",t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
    }
    qFindSamples[t1]=finish;
    DBGPRINT("  FUNC:getQFindSamples [t1=%d]finish(%d|%d)->(quesx=%d,quesy=%d)  |finish with finishSample\n",t1,finish._x+gddx,finish._y+gddy,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
#ifdef DBGFLAG
    for(t1=0;t1<numQFindSamples;t1++){//lineSamples
        DBGPRINT("  FUNCOUT:getQFindSamples[%d]->[x=%d|y=%d]\n",t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
    }
#endif
}
int getBarWidthCorrectPoint(DataDigital* indata, double invslope, PairXY* io_point, int correctPoint){
    int tx,ty,width=0,whiteWidth,tvalue;
    PairXY tpoint,point,blackPoint,minx,maxx;
    point=*io_point;
    tpoint=point;minx=tpoint;maxx=tpoint;
    tvalue = getValue(indata,point._x,point._y);
    blackPoint = point;
    if(tvalue==0){
        //Find the first black
        for(tx=1;tx<PIXELSPERPENLINE;tx++){
            ty=roundOffSignRobust(-1*invslope*(tx));
            tpoint._x=point._x+tx; tpoint._y=point._y+ty;
            tvalue = getValue(indata,tpoint._x,tpoint._y);
            if(tvalue==1){ blackPoint._x=tpoint._x; blackPoint._y=tpoint._y; width=1;break; }
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
            tpoint._x=point._x-tx; tpoint._y=point._y-ty;
            tvalue = getValue(indata,tpoint._x,tpoint._y);
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
            if(tvalue==1){ blackPoint._x=tpoint._x; blackPoint._y=tpoint._y; width=1;break; }
        }
    }else{
        width=1;
    }
    whiteWidth=0;
    for(tx=1;tx<PIXELSPERPENLINE;tx++){
        ty=roundOffSignRobust(-1*invslope*(tx));
        tpoint._x=blackPoint._x+tx; tpoint._y=blackPoint._y+ty;
        tvalue = getValue(indata,tpoint._x,tpoint._y);
        LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint [tpointx=%d|tpointy=%d]->(tvalue=%X)->(width=%d)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue,width);
        if(tvalue==1){width=width+whiteWidth+1; whiteWidth=0;}
        else{ if(whiteWidth>=PIXELSDIRTWHITEDOT){break;} whiteWidth++;}
    }
    maxx._x=blackPoint._x+tx; maxx._y=blackPoint._y+ty;
    whiteWidth=0;
    for(tx=1;tx<PIXELSPERPENLINE;tx++){
        ty=roundOffSignRobust(-1*invslope*(tx));
        tpoint._x=blackPoint._x-tx; tpoint._y=blackPoint._y-ty;
        tvalue = getValue(indata,tpoint._x,tpoint._y);
        LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint [tpointx=%d|tpointy=%d]->(tvalue=%X)->(width=%d)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue,width);
        if(tvalue==1){width=width+whiteWidth+1; whiteWidth=0;}
        else{ if(whiteWidth>=PIXELSDIRTWHITEDOT){break;} whiteWidth++;}
    }
    minx._x=blackPoint._x-tx; minx._y=blackPoint._y-ty;

    LOPPRINT("  FUNC:getBarWidthCorrectPoint (%d,%d)->(width=%d)\n",io_point->_x+gddx,io_point->_y+gddy,width);
    if(width>=PIXELSPERPENLINE || width<=PIXELSDIRTBLACKDOT){return 0;}
    if(correctPoint==1){
        (*io_point) = getMidpoint(minx,maxx);
        LOPPRINT("  FUNCOUT:getBarWidthCorrectPoint(minx=%d|miny=%d|maxx=%d|maxy=%d) OUT->(iopointx=%d,iopointy=%d)\n",minx._x+gddx,minx._y+gddy,maxx._x+gddx,maxx._y+gddy,io_point->_x+gddx,io_point->_y+gddy);
    }
    return width;
}
int barWidthGetCriterion(int *barWidth, int barWidthArrSize, ChebyshevCriterion* ccLine, ChebyshevCriterion* ccBar){
    int t1,t2,maxBarWidth,numOfWidths;
    int* freqBarWidth=NULL;
    int* indexBarWidth=NULL;
    ChebyshevCriterion cc;
    maxBarWidth=0;
    for(t1=0;t1<barWidthArrSize;t1++){
        if(maxBarWidth<barWidth[t1]){
            maxBarWidth=barWidth[t1];
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion(maxBarWidth=%d)\n",maxBarWidth);
        }
    }
    indexBarWidth = (int*) malloc(maxBarWidth*sizeof(int));
    freqBarWidth = (int*) malloc(maxBarWidth*sizeof(int));
    if(indexBarWidth==NULL || freqBarWidth==NULL){
        if(indexBarWidth!=NULL){free(indexBarWidth);indexBarWidth=NULL;}
        if(freqBarWidth!=NULL){free(freqBarWidth);freqBarWidth=NULL;}
        DBGPRINT("  FUNCOUT:barWidthGetCriterion(indexBarWidth=%X|freqBarWidth=%X)\n",indexBarWidth,freqBarWidth);
        return 1;
    }
    numOfWidths=0;
    //for(t1=0;t1<numOfWidths;t1++){indexBarWidth[t1]=0;freqBarWidth[t1]=0;} //NOT NEEDED GUESS WHY?
    for(t1=0;t1<barWidthArrSize;t1++){
        if(barWidth[t1]==0){continue;}
        for(t2=0;t2<numOfWidths;t2++){
            if(barWidth[t1]==indexBarWidth[t2]){freqBarWidth[t2]++; break;}
        }
        if(t2==numOfWidths){
            for(t2=numOfWidths;t2>0;t2--){
                if(barWidth[t1]>indexBarWidth[t2-1]){break;}
                freqBarWidth[t2]=freqBarWidth[t2-1];
                indexBarWidth[t2]=indexBarWidth[t2-1];
            }
            freqBarWidth[t2]=1;
            indexBarWidth[t2]=barWidth[t1];
            numOfWidths++;
        }
        LOPPRINT("  FUNCLOOP:barWidthGetCriterion(t2=%d)->(indexBarWidth=%d|freqBarWidth=%d)\n",t2,indexBarWidth[t2],freqBarWidth[t2]);
    }
#ifdef DBGFLAG
    for(t2=0;t2<numOfWidths;t2++){//lineSamples
        DBGPRINT("  FUNCOUT:barWidthGetCriterion KmeansArray[%d]->(indexBarWidth=%d|freqBarWidth=%d)\n",t2,indexBarWidth[t2],freqBarWidth[t2]);
    }
#endif
    //Kmeans Algorithm
    double mean1, mean2;
    int tot1,tot2,kmeansindex,isChanged;
    for(t2=1;t2<numOfWidths-1;t2++){
        mean1=0;tot1=0;
        for(t1=0;t1<t2;t1++){
            mean1=mean1+(indexBarWidth[t1]*freqBarWidth[t1]);
            tot1=tot1+freqBarWidth[t1];
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-KMeansAlgorithmMean1(KMeansIndex=%d|t1=%d)->(total1=%lf|num1=%d)\n",t2,t1,mean1,tot1);
        }
        mean1=mean1/tot1;
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmMean1(KMeansIndex=%d|t1=%d)->(mean1=%lf|num1=%d)\n",t2,t1,mean1,tot1);
        mean2=0;tot2=0;
        for(t1=t2;t1<numOfWidths;t1++){
            mean2=mean2+(indexBarWidth[t1]*freqBarWidth[t1]);
            tot2=tot2+freqBarWidth[t1];
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-KMeansAlgorithmMean2(KMeansIndex=%d|t1=%d)->(total2=%lf|num2=%d)\n",t2,t1,mean2,tot2);
        }
        mean2=mean2/tot2;
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmMean2(KMeansIndex=%d|t1=%d)->(mean2=%lf|num2=%d)\n",t2,t1,mean2,tot2);
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmToAnalyze(KMeansIndex=%d|t1=%d)->(mean1=%lf|num1=%d|mean2=%lf|num2=%d)\n",t2,t1,mean1,tot1,mean2,tot2);
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmDeviationFromMean(KMeansIndex=%d|t1=%d)->(mean1=%lf|mean2=%lf|deviationfrom1=%lf|deviationfrom2=%lf)\n",t2,t1,mean1,mean2,absValDouble(indexBarWidth[t2]-mean1),absValDouble(indexBarWidth[t2]-mean2));
        if(absValDouble(indexBarWidth[t2]-mean2)<absValDouble(indexBarWidth[t2]-mean1)){
            break;
        }
    }
    kmeansindex=t2;
    DBGPRINT("  FUNCOUT:barWidthGetCriterion-KMeansAlgorithm(FinalKMeansIndex=%d)\n",kmeansindex);


    isChanged=1;
    while(isChanged==1){
        isChanged=0;
        getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth, 0,kmeansindex);
        for(t1=0;t1<kmeansindex;t1++){
            if(freqBarWidth[t1]==0){continue;}
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Line(BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf)\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
            if(getKFromChebyshev(cc,indexBarWidth[t1])>CHEBYCHEVKVALUEWIDTH){
                LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Line(BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf) |  delete this, too much deviation\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
                freqBarWidth[t1]=0;
                isChanged=1;
            }
        }
    }
    getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth, 0,kmeansindex);
    DBGPRINT("  FUNCOUT:barWidthGetCriterion-Line(FinalLineMean:%lf, FinalLineStdDev:%lf\n",cc.mean,cc.stddev);
    *ccLine=cc;

    isChanged=1;
    while(isChanged==1){
        isChanged=0;
        getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth,kmeansindex,numOfWidths);
        for(t1=kmeansindex;t1<numOfWidths;t1++){
            if(freqBarWidth[t1]==0){continue;}
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Bar (BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf)\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
            if(getKFromChebyshev(cc,indexBarWidth[t1])>CHEBYCHEVKVALUEWIDTH){
                LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Bar (BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf) |  delete this, too much deviation\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
                freqBarWidth[t1]=0;
                isChanged=1;
            }
        }
    }
    getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth,kmeansindex,numOfWidths);
    DBGPRINT("  FUNCOUT:barWidthGetCriterion-Bar (FinalBarMean:%lf, FinalBarStdDev:%lf\n",cc.mean,cc.stddev);
    *ccBar=cc;

    free(freqBarWidth);freqBarWidth=NULL;
    free(indexBarWidth);indexBarWidth=NULL;
    return 0;
}
void getQuestions(DataDigital* dd, PairXY* in_questions, int* in_numQuestion, PairXY* qFindSamples, int* qFindSamplesType, int* barWidth, int numQFindSamples, LineSlopeIntercept tslopeintercept, ChebyshevCriterion ccLine, ChebyshevCriterion ccBar){
    int t1,t2,numQuestion=0,type,prevtype,twidth,numImptCoor,numBarHeightArr,saved;
    double tdouble,tempBarHeight;
    int* barHeightArr;
    int correctPosition,limitY;
    ChebyshevCriterion cc;
    PairXY prevpair,bgnpair,endpair,tmppair;
    PairXY bgnpair2,endpair2;
    prevtype = 0;
    prevpair = qFindSamples[0];
    numImptCoor=0;
    for(t1=0;t1<numQFindSamples;t1++){
        if(barWidth[t1]<=PIXELSDIRTBLACKDOT){
            type=0;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [Dirt] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }else if(getKFromChebyshev(ccLine,barWidth[t1])<CHEBYCHEVKVALUEWIDTH){
            type=1;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [Line] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }else if(getKFromChebyshev(ccBar,barWidth[t1])<CHEBYCHEVKVALUEWIDTH){
            type=2;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [Bar] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }else{
            type=0;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [No Class] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }
        if(prevtype==0 && type==0 && t1!=0){//both no class case
            bgnpair = prevpair;
            endpair = qFindSamples[t1];
            bgnpair2._x=endpair._x-bgnpair._x; bgnpair2._y=endpair._y-bgnpair._y;
            limitY=0;
            t2=1;
            while(t2<bgnpair2._y){
                tmppair._x = roundOffSignRobust(((double)t2*bgnpair2._x/bgnpair2._y)+bgnpair._x);
                tmppair._y = roundOffSignRobust(bgnpair._y+t2);
                twidth = getBarWidthCorrectPoint(dd, tslopeintercept.slope, &tmppair, 0);
                DBGPRINT("  FUNC:getQuestions-NoClassToNoClass[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line
                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
                    qFindSamples[t1] = tmppair;
                    barWidth[t1]=twidth;
                    limitY=1;
                    break;
                }else if(getKFromChebyshev(ccBar,twidth)<CHEBYCHEVKVALUEWIDTH){
                    qFindSamples[t1] = tmppair;
                    barWidth[t1]=twidth;
                    limitY=1;
                    break;
                }
                t2=t2+1;
            }
            if(limitY==1){
                t1=t1-1;
                continue;
            }
        }else if((prevtype==0 && type==2) || (prevtype==1 && type==2)){
            bgnpair = prevpair;
            endpair = qFindSamples[t1];
            limitY=endpair._y-bgnpair._y;
            correctPosition=1;
            while(limitY>1){
                bgnpair2 = bgnpair; endpair2 = endpair;
                tmppair = getMidpoint(bgnpair2,endpair2);
                twidth = getBarWidthCorrectPoint(dd, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-LineToBar[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line
                    bgnpair2 = tmppair;
                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
                    bgnpair2 = tmppair;
                }else if(getKFromChebyshev(ccBar,twidth)<CHEBYCHEVKVALUEWIDTH){
                    endpair2 = tmppair;
                }else{//assume line
                    bgnpair2 = tmppair;
                }
                if(endpair2._y-bgnpair2._y<limitY){
                    bgnpair = bgnpair2; endpair = endpair2; limitY=endpair._y-bgnpair._y;
                    correctPosition=1;
                }else{
                    correctPosition=0;
                }
            }
            qFindSamples[numImptCoor] = endpair;
            qFindSamplesType[numImptCoor] = 1; //line to bar
            numImptCoor++;
        }else if((prevtype==2 && type==0) || (prevtype==2 && type==1)){
            bgnpair = prevpair;
            endpair = qFindSamples[t1];
            limitY=endpair._y-bgnpair._y;
            correctPosition=1;
            while(endpair._y-bgnpair._y>1){
                bgnpair2 = bgnpair; endpair2 = endpair;
                tmppair = getMidpoint(bgnpair2,endpair2);
                twidth = getBarWidthCorrectPoint(dd, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-BarToLine[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line
                    endpair2 = tmppair;
                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
                    endpair2 = tmppair;
                }else if(getKFromChebyshev(ccBar,twidth)<CHEBYCHEVKVALUEWIDTH){
                    bgnpair2 = tmppair;
                }else{//assume line
                    endpair2 = tmppair;
                }
                if(endpair2._y-bgnpair2._y<limitY){
                    bgnpair = bgnpair2; endpair = endpair2; limitY=endpair._y-bgnpair._y;
                    correctPosition=1;
                }else{
                    correctPosition=0;
                }
            }
            qFindSamples[numImptCoor] = bgnpair;
            qFindSamplesType[numImptCoor] = 2; //bar to line
            numImptCoor++;
        }
        if(t1==numQFindSamples-1 && type==2){ //last bar
            qFindSamples[numImptCoor] = qFindSamples[t1]; //add point if last bar
            qFindSamplesType[numImptCoor] = 2;
            numImptCoor++;
        }
        prevpair = qFindSamples[t1];
        prevtype = type;
    }

    //Get Bar Height
    barHeightArr=malloc(numImptCoor*sizeof(int));
    if(barHeightArr==NULL){INFPRINT("ERROR: Error in allocating barHeightArr array.\n"); return;}

    numBarHeightArr=0;
    saved=0;
    prevpair = qFindSamples[0];
    for(t1=0;t1<numImptCoor;t1++){
        DBGPRINT("  FUNC:getQuestions barHeightArr[%d]|type:%d->(%d,%d)\n",t1,qFindSamplesType[t1],qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
        if(qFindSamplesType[t1]==1){ prevpair = qFindSamples[t1]; saved=1;
        }else if(qFindSamplesType[t1]==2 && saved==1){
            tempBarHeight = getBarHeight(qFindSamples[t1],prevpair);
            if (BARHEIGHTLOW<tempBarHeight && BARHEIGHTHIGH>tempBarHeight){
                DBGPRINT("  FUNC:getQuestions barHeightArr[%d]|type:%d->[numBar:%d](%d-%d=%d)\n",t1,qFindSamplesType[t1],numBarHeightArr,qFindSamples[t1]._y+gddy,prevpair._y+gddy,qFindSamples[t1]._y-prevpair._y);
                barHeightArr[numBarHeightArr++] = (int)tempBarHeight;
            }
        }
    }
    getChebyshevInt(&cc, barHeightArr, numBarHeightArr);
    prevpair = qFindSamples[0];
    numQuestion=0;
    for(t1=0;t1<numImptCoor;t1++){
        if(qFindSamplesType[t1]==1){
            prevpair = qFindSamples[t1];
            DBGPRINT("  FUNC:getQuestions[%d](%d,%d) Type:1 \n",t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
            tdouble = BARHEIGHTHIGH-BARHEIGHTLOW;// assign properlimit;
            saved=0;
            for(t2=t1+1;t2<numImptCoor;t2++){
                tempBarHeight = getBarHeight(qFindSamples[t2],prevpair);
                DBGPRINT("  FUNC:getQuestions[%d]->(height=%lf)<(%lf):(MeanBarHeight=%lf)\n",t2,tempBarHeight,tdouble,cc.mean);
                if(qFindSamplesType[t2]==2 && BARHEIGHTLOW<tempBarHeight && BARHEIGHTHIGH>tempBarHeight && absValDouble(tempBarHeight-cc.mean)<tdouble){
                    DBGPRINT("  FUNC:getQuestions[%d] Question endpoint candidate (%d,%d)(%d,%d)->height(%d):(Mean(k)=%lf)\n",
                    t2,prevpair._x+gddx,prevpair._y+gddy,qFindSamples[t2]._x+gddx,qFindSamples[t2]._y+gddy,tempBarHeight,cc.mean);
                    in_questions[numQuestion]._x=prevpair._x; in_questions[numQuestion]._y=prevpair._y;
                    in_questions[numQuestion+1]._x=qFindSamples[t2]._x; in_questions[numQuestion+1]._y=qFindSamples[t2]._y;
                    tdouble = absValDouble(tempBarHeight-cc.mean);
                    t1=t2;
                    saved=1;
                }
                if(tempBarHeight>BARHEIGHTHIGH){ break;}
            }
            if(saved==1){
                DBGPRINT("  FUNC:getQuestions: Endpoint ADDED\n");
                numQuestion=numQuestion+2;
            }
        }
    }

    free(barHeightArr);barHeightArr=NULL;

#ifdef DBGFLAG
    for(t1=0;t1<numQuestion;t1++){//lineSamples
        DBGPRINT("FUNCOUT:getQuestions[%d]->[x=%d|y=%d]\n",t1,in_questions[t1]._x+gddx,in_questions[t1]._y+gddy);
    }
#endif
    *in_numQuestion=numQuestion;
}

int getQuestionsFromLine(DataDigital* in_dd, PairXY* out_questions, int numExpectedQuestions, double* tdoublearr, LineSlopeIntercept tslopeintercept, PairXY tcornerup, PairXY tcornerdown, int barheightsamplepixels){
    ChebyshevCriterion ccLine,ccBar,ccBarHeight;
    PairXY* qFindSamples=NULL;
    int* barWidth=NULL;
    int* qFindSamplesType=NULL;
    int numQFindSamples, numQuestionsCoor;
    int t1=0,fail=0;
    double temp;
    do{
        numQFindSamples = rasterRound(((double)tcornerdown._y-tcornerup._y)/barheightsamplepixels)+1;
        if(numQFindSamples<numExpectedQuestions){INFPRINT("ERROR: Number of QFindSamples is not enough.\n"); fail=1;break;}
        qFindSamples=(PairXY*)malloc(numQFindSamples*sizeof(PairXY));
        if(qFindSamples==NULL){INFPRINT("ERROR: Error in allocating qFindSamples array.\n"); fail=1;break;}
        qFindSamplesType=(int*)malloc(numQFindSamples*sizeof(PairXY));
        if(qFindSamplesType==NULL){INFPRINT("ERROR: Error in allocating qFindSamplesType array.\n"); fail=1;break;}
        getQFindSamples(qFindSamples, numQFindSamples, tcornerup, tcornerdown, tslopeintercept, barheightsamplepixels);
        barWidth=(int*)malloc(numQFindSamples*sizeof(int));
        if(barWidth==NULL){INFPRINT("ERROR: Error in allocating BarWidth array.\n"); fail=1;break;}
        for(t1=0;t1<numQFindSamples;t1++){barWidth[t1] = getBarWidthCorrectPoint(in_dd, tslopeintercept.slope, &(qFindSamples[t1]),1);}
        if(barWidthGetCriterion(barWidth, numQFindSamples, &ccLine, &ccBar)==1){
            INFPRINT("ERROR: Error in allocating IndexBarWidth and FreqBarWidth array.\n"); fail=1;break;
        }
        getQuestions(in_dd, out_questions, &numQuestionsCoor, qFindSamples, qFindSamplesType, barWidth, numQFindSamples, tslopeintercept, ccLine, ccBar);
        free(barWidth);barWidth=NULL;
        free(qFindSamples);qFindSamples=NULL;
        free(qFindSamplesType);qFindSamplesType=NULL;
        if(numQuestionsCoor%2==1){INFPRINT("ERROR: Error in finding questions. Odd number of coordinates for the bars.\n"); fail=1;break;}
        if(numExpectedQuestions*2!=numQuestionsCoor){INFPRINT("ERROR: Number of questions does not match with expected number\n"); fail=1;break;}
        //for(t1=0;t1<numQuestionsCoor;t1++){getBarWidthCorrectPoint(in_dd, tslopeintercept.slope, &(out_questions[t1]),1);}
        //for(t1=0;t1<numQuestionsCoor;t1++){if(absValDouble((tslopeintercept.slope*out_questions[t1]._y)+tslopeintercept.intercept-out_questions[t1]._x)>(ccLine.mean*ALLOWANCEMULT)){fail=1;break;}}
        //if(fail==1){INFPRINT("ERROR: Error in finding questions. The coordinates of the bars are wrong. Coordinates(%d,%d)\n",out_questions[t1]._x,out_questions[t1]._y); fail=1;break;}
        getBarHeightArr(out_questions,tdoublearr, numQuestionsCoor);
        //getChebyshevDouble(&ccBarHeight, tdoublearr, numExpectedQuestions);
        for(t1=0;t1<numExpectedQuestions;t1++){
            //temp = getKFromChebyshev(ccBarHeight,tdoublearr[t1]);
            //DBGPRINT("  FUNCOUT:getQuestionsFromLine(BarHeight)[%d] -> ( barHeight=%lf Deviation=%lf Limit=%lf)\n",t1,tdoublearr[t1],temp,(double)CHEBYCHEVKVALUEHEIGHT);
            DBGPRINT("  FUNCOUT:getQuestionsFromLine(BarHeight)[%d] -> ( barHeight=%lf)\n",t1,tdoublearr[t1]);
            //if(temp>CHEBYCHEVKVALUEHEIGHT){ fail=1;break;}
            if(!(BARHEIGHTLOW<tdoublearr[t1] && BARHEIGHTHIGH>tdoublearr[t1])){ fail=1;break;}
        }
        if(fail==1){INFPRINT("ERROR: Error in finding questions. Invalid BarHeightFound.\n"); fail=1;break;}
        for(t1=0;t1<numQuestionsCoor;t1++){
            DBGPRINT("  FUNCOUT:getQuestionsFromLine[%d] -> (x=%d,y=%d)\n",(t1/2)+1,out_questions[t1]._x+gddx,out_questions[t1]._y+gddy);
            out_questions[t1]._x=out_questions[t1]._x+in_dd->xlow; out_questions[t1]._y=out_questions[t1]._y+in_dd->ylow;
        }
    }while(0);
    if(qFindSamples!=NULL){free(qFindSamples);qFindSamples=NULL;}
    if(qFindSamplesType!=NULL){free(qFindSamplesType);qFindSamplesType=NULL;}
    if(barWidth!=NULL){free(barWidth);barWidth=NULL;}
    return fail;
}

int processOneFile(char* fileName){

    BmpImage img;
    DataDigital dd;
    ChebyshevCriterion ccSlope;
    dd.buf = NULL;//IMPT
    dd.status=0;
    if(openBmpImage(&img,fileName)){
        INFPRINT("ERROR: Error in Reading BMP File. BMP File: [%s]\n",fileName);
        closeBmpImage(&img);
        return 1;
    }
    if(img.xSize<=PIXELSPERPENLINE || img.ySize<=PIXELSPERPENLINE){
        INFPRINT("ERROR: BMP File is too small (%d pixels by % pixels only).\n",PIXELSPERPENLINE,PIXELSPERPENLINE);
        closeBmpImage(&img);
        return 1;
    }

    INFPRINT("processOneFile: %s\n",fileName);

    //forfaster
    int barheightsamplepixels = 10;
    int xsearchsize = img.xSize/8;
    int ysearchsize = img.ySize/8;

    LineSlopeIntercept leftline, rightline, topline, bottomline, centerleftline, centerrightline, templine;
    PairXY uplfcorner, uprtcorner, dnlfcorner, dnrtcorner, upcenter, dncenter;
    PairXY temppoint1,temppoint2,temppoint3;
    PairXY lineSamples[SAMPLESLINETOALLOC];
    PairXY Q1[MAXQUESTIONSCOOR],Q2[MAXQUESTIONSCOOR],Q3[MAXQUESTIONSCOOR],Q4[MAXQUESTIONSCOOR];
    int numLineSamples,maxLineSamples;
    double tdoublearr[SAMPLESLINETOALLOC];
    int t1, algoTries;

    algoTries=0;
    while(algoTries<2){//Two Tries only
        cleanDataDigital(&dd);
        if(algoTries==0){
            //algoTries++;continue;//DELETETHIS pnly test robust case
            maxLineSamples=SAMPLESLINE;
            //Left Line
            INFPRINT("INFO: Finding left line. NumOfSamples=%d\n",maxLineSamples);
            addPointToDataDigital(&img,&dd,0,0); addPointToDataDigital(&img,&dd,xsearchsize,img.ySize-1);
            if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
            if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(0,0),createXY(0,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            leftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            leftline.slope=ccSlope.mean;
            leftline = transposeLine(leftline,0,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
            //Right Line
            INFPRINT("INFO: Finding right line. NumOfSamples=%d\n",maxLineSamples);
            addPointToDataDigital(&img,&dd,img.xSize-1-xsearchsize,0); addPointToDataDigital(&img,&dd,img.xSize-1,img.ySize-1);
            if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
            if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(xsearchsize-1,0),createXY(xsearchsize-1,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            rightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            rightline.slope=ccSlope.mean;
            rightline = transposeLine(rightline,0,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
            maxLineSamples=SAMPLESLINETOPBOTTOM;
            //Top Line
            INFPRINT("INFO: Finding top line. NumOfSamples=%d\n",maxLineSamples);
            addPointToDataDigital(&img,&dd,0,0); addPointToDataDigital(&img,&dd,img.xSize-1,ysearchsize);
            if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
            if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromTop(&dd, lineSamples,maxLineSamples, createXY(0,0),createXY(img.xSize-1,0));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINETOPBOTTOM>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            topline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            topline.slope=ccSlope.mean;
            topline = transposeLine(topline,1,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
            //Bottom Line
            INFPRINT("INFO: Finding bottom line. NumOfSamples=%d\n",maxLineSamples);
            addPointToDataDigital(&img,&dd,0,img.ySize-1-ysearchsize); addPointToDataDigital(&img,&dd,img.xSize-1,img.ySize-1);
            if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
            if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromBottom(&dd, lineSamples,maxLineSamples, createXY(0,ysearchsize-1),createXY(img.xSize-1,ysearchsize-1));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINETOPBOTTOM>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            bottomline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            bottomline.slope=ccSlope.mean;
            bottomline = transposeLine(bottomline,1,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
        }else if(algoTries==1){
            INFPRINT("\nINFO: Retesting with more robust parameters\n");
            maxLineSamples=ROBUSTSAMPLESLINE;
            INFPRINT("INFO: Allocating whole Image. This may take a lot of resources and time\n",maxLineSamples);
            addPointToDataDigital(&img,&dd,0,0); addPointToDataDigital(&img,&dd,img.xSize-1,img.ySize-1);
            if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
            if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
            //Left Line
            INFPRINT("INFO: Finding left line. NumOfSamples=%d\n",maxLineSamples);
            numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(0,0),createXY(0,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            leftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            leftline.slope=ccSlope.mean;
            //Right Line
            INFPRINT("INFO: Finding right line. NumOfSamples=%d\n",maxLineSamples);
            numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(img.xSize-1,0),createXY(img.xSize-1,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            rightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            rightline.slope=ccSlope.mean;
            maxLineSamples=ROBUSTSAMPLESLINETOPBOTTOM;
            //Top Line
            INFPRINT("INFO: Finding top line. NumOfSamples=%d\n",maxLineSamples);
            numLineSamples = findLineImageFromTop(&dd, lineSamples,maxLineSamples, createXY(0,0),createXY(img.xSize-1,0));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINETOPBOTTOM, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            topline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            topline.slope=ccSlope.mean;
            //Bottom Line
            INFPRINT("INFO: Finding bottom line. NumOfSamples=%d\n",maxLineSamples);
            numLineSamples = findLineImageFromBottom(&dd, lineSamples,maxLineSamples, createXY(0,img.ySize-1),createXY(img.xSize-1,img.ySize-1));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINETOPBOTTOM, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            bottomline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            bottomline.slope=ccSlope.mean;
        }

        DBGPRINT("INFO: LeftLine (slope=%lf|intercept=%lf)\n",leftline.slope,leftline.intercept);
        DBGPRINT("INFO: RightLine (slope=%lf|intercept=%lf)\n",rightline.slope,rightline.intercept);
        DBGPRINT("INFO: TopLine (slope=%lf|intercept=%lf)\n",topline.slope,topline.intercept);
        DBGPRINT("INFO: BottomLine (slope=%lf|intercept=%lf)\n",bottomline.slope,bottomline.intercept);
        uplfcorner = findIntersection(leftline,topline);
        uprtcorner = findIntersection(rightline,topline);
        dnlfcorner = findIntersection(leftline,bottomline);
        dnrtcorner = findIntersection(rightline,bottomline);
        upcenter = getMidpoint(uplfcorner,uprtcorner);
        dncenter = getMidpoint(dnlfcorner,dnrtcorner);
        DBGPRINT("INFO: UpLeftCorner (x=%d,y=%d)\n",uplfcorner._x,uplfcorner._y);
        DBGPRINT("INFO: UpRightCorner (x=%d,y=%d)\n",uprtcorner._x,uprtcorner._y);
        DBGPRINT("INFO: DownLeftCorner (x=%d,y=%d)\n",dnlfcorner._x,dnlfcorner._y);
        DBGPRINT("INFO: DownRightCorner (x=%d,y=%d)\n",dnrtcorner._x,dnrtcorner._y);
        if(checkIfWithinImageBounds(uplfcorner,img.xSize-1,img.ySize-1)==1){INFPRINT("ERROR: Invalid UpLeftCorner point.\n");algoTries++;continue;}
        if(checkIfWithinImageBounds(uprtcorner,img.xSize-1,img.ySize-1)==1){INFPRINT("ERROR: Invalid UpRightCorner point.\n");algoTries++;continue;}
        if(checkIfWithinImageBounds(dnlfcorner,img.xSize-1,img.ySize-1)==1){INFPRINT("ERROR: Invalid DownLeftCorner point.\n");algoTries++;continue;}
        if(checkIfWithinImageBounds(dnrtcorner,img.xSize-1,img.ySize-1)==1){INFPRINT("ERROR: Invalid DownRightCorner point.\n");algoTries++;continue;}
        if(algoTries==0){
            barheightsamplepixels=10;
            //Q1
            addPointToDataDigital(&img,&dd,uplfcorner._x-PIXELSSEARCHSIZE,uplfcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,uplfcorner._x+PIXELSSEARCHSIZE,uplfcorner._y+PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnlfcorner._x-PIXELSSEARCHSIZE,dnlfcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnlfcorner._x+PIXELSSEARCHSIZE,dnlfcorner._y+PIXELSSEARCHSIZE);
            if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
            if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
            temppoint1 = transposePoint(uplfcorner,dd.xlow,dd.ylow);
            temppoint2 = transposePoint(dnlfcorner,dd.xlow,dd.ylow);
            templine=transposeLine(leftline,0,dd.xlow,dd.ylow);
            if(getQuestionsFromLine(&dd,Q1,numQuestionCol1,tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1){
                INFPRINT("ERROR: Error in finding questions in left line.\n");algoTries++;continue;
            }
            deAllocData(&dd);
            //Q4
            addPointToDataDigital(&img,&dd,uprtcorner._x-PIXELSSEARCHSIZE,uprtcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,uprtcorner._x+PIXELSSEARCHSIZE,uprtcorner._y+PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnrtcorner._x-PIXELSSEARCHSIZE,dnrtcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnrtcorner._x+PIXELSSEARCHSIZE,dnrtcorner._y+PIXELSSEARCHSIZE);
            if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
            if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
            temppoint1 = transposePoint(uprtcorner,dd.xlow,dd.ylow);
            temppoint2 = transposePoint(dnrtcorner,dd.xlow,dd.ylow);
            templine=transposeLine(rightline,0,dd.xlow,dd.ylow);
            if(getQuestionsFromLine(&dd,Q4,numQuestionCol2,tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1){
                INFPRINT("ERROR: Error in finding questions in right line.\n");algoTries++;continue;
            }
            deAllocData(&dd);
            if(numColumns==2){
                temppoint1=getMidpoint(uplfcorner,upcenter);
                temppoint2=getMidpoint(upcenter,uprtcorner);
                addPointToDataDigital(&img,&dd,temppoint1._x,temppoint1._y-PIXELSSEARCHSIZE);
                addPointToDataDigital(&img,&dd,temppoint2._x,temppoint2._y-PIXELSSEARCHSIZE);
                temppoint1=getMidpoint(dnlfcorner,dncenter);
                temppoint2=getMidpoint(dncenter,dnrtcorner);
                addPointToDataDigital(&img,&dd,temppoint1._x,temppoint1._y+PIXELSSEARCHSIZE);
                addPointToDataDigital(&img,&dd,temppoint2._x,temppoint2._y+PIXELSSEARCHSIZE);
                if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
                if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
                maxLineSamples=SAMPLESLINE;
                //center left line
                temppoint1 = transposePoint(upcenter,dd.xlow,dd.ylow);
                temppoint2 = transposePoint(dncenter,dd.xlow,dd.ylow);
                INFPRINT("INFO: Finding center left line. NumOfSamples=%d\n",maxLineSamples);
                numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,temppoint1,temppoint2);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(MINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerleftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerleftline.slope=ccSlope.mean;
                centerleftline=transposeLine(centerleftline,0,-1*dd.xlow,-1*dd.ylow);
                //Q2
                temppoint1 = findIntersection(centerleftline,topline);temppoint1 = transposePoint(temppoint1,dd.xlow,dd.ylow);
                temppoint2 = findIntersection(centerleftline,bottomline);temppoint2 = transposePoint(temppoint2,dd.xlow,dd.ylow);
                templine = transposeLine(centerleftline,0,dd.xlow,dd.ylow);
                if(getQuestionsFromLine(&dd,Q2,numQuestionCol1,tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1){
                    INFPRINT("ERROR: Error in finding questions in center left line.\n");algoTries++;continue;
                }
                //center right line
                temppoint1 = transposePoint(upcenter,dd.xlow,dd.ylow);
                temppoint2 = transposePoint(dncenter,dd.xlow,dd.ylow);
                INFPRINT("INFO: Finding center right line. NumOfSamples=%d\n",maxLineSamples);
                numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,temppoint1,temppoint2);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(MINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerrightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerrightline.slope=ccSlope.mean;
                centerrightline=transposeLine(centerrightline,0,-1*dd.xlow,-1*dd.ylow);
                //Q3
                temppoint1 = findIntersection(centerrightline,topline);temppoint1 = transposePoint(temppoint1,dd.xlow,dd.ylow);
                temppoint2 = findIntersection(centerrightline,bottomline);temppoint2 = transposePoint(temppoint2,dd.xlow,dd.ylow);
                templine = transposeLine(centerrightline,0,dd.xlow,dd.ylow);
                if(getQuestionsFromLine(&dd,Q3,numQuestionCol2,tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1){
                    INFPRINT("ERROR: Error in finding questions in center right line.\n");algoTries++;continue;
                }
                deAllocData(&dd);
            }
        }else if(algoTries==1){
            barheightsamplepixels=5;
            //Q1
            if(getQuestionsFromLine(&dd,Q1,numQuestionCol1,tdoublearr,leftline,uplfcorner,dnlfcorner,barheightsamplepixels)==1){
                INFPRINT("ERROR: Error in finding questions in left line.\n");algoTries++;continue;
            }
            //Q4
            if(getQuestionsFromLine(&dd,Q4,numQuestionCol2,tdoublearr,rightline,uprtcorner,dnrtcorner,barheightsamplepixels)==1){
                INFPRINT("ERROR: Error in finding questions in right line.\n");algoTries++;continue;
            }
            if(numColumns==2){
                maxLineSamples=ROBUSTSAMPLESLINE;
                //center left line
                INFPRINT("INFO: Finding center left line. NumOfSamples=%d\n",maxLineSamples);
                numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,upcenter,dncenter);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(ROBUSTMINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerleftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerleftline.slope=ccSlope.mean;
                //Q2
                temppoint1 = findIntersection(centerleftline,topline);
                temppoint2 = findIntersection(centerleftline,bottomline);
                if(getQuestionsFromLine(&dd,Q2,numQuestionCol1,tdoublearr,centerleftline,temppoint1,temppoint2,barheightsamplepixels)==1){
                    INFPRINT("ERROR: Error in finding questions in center left line.\n");algoTries++;continue;
                }
                //center right line
                INFPRINT("INFO: Finding center right line. NumOfSamples=%d\n",maxLineSamples);
                numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,upcenter,dncenter);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(ROBUSTMINSAMPLESLINE>numLineSamples){INFPRINT("ERROR: Error in finding the line. Number of samples is not enough (numLineSamples=%d).\n",numLineSamples);algoTries++;continue;}
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1){INFPRINT("ERROR: Invalid Slope.\n");algoTries++;continue;}
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerrightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerrightline.slope=ccSlope.mean;
                //Q3
                temppoint1 = findIntersection(centerrightline,topline);
                temppoint2 = findIntersection(centerrightline,bottomline);
                if(getQuestionsFromLine(&dd,Q3,numQuestionCol2,tdoublearr,centerrightline,temppoint1,temppoint2,barheightsamplepixels)==1){
                    INFPRINT("ERROR: Error in finding questions in center right line.\n");algoTries++;continue;
                }
            }
        }
        if(algoTries==0){
            if(numColumns==2){
                //COL1
                addPointToDataDigital(&img,&dd,uplfcorner._x,uplfcorner._y);
                addPointToDataDigital(&img,&dd,dnlfcorner._x,dnlfcorner._y);
                addPointToDataDigital(&img,&dd,upcenter._x,upcenter._y);
                addPointToDataDigital(&img,&dd,dncenter._x,dncenter._y);
                if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
                if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
                if(processOneColumn(&dd, Q1, Q2, numQuestionCol1, 1)){INFPRINT("ERROR: Error in finding number circles.\n");algoTries++;continue;}
                deAllocData(&dd);
                //COL2
                addPointToDataDigital(&img,&dd,upcenter._x,upcenter._y);
                addPointToDataDigital(&img,&dd,dncenter._x,dncenter._y);
                addPointToDataDigital(&img,&dd,uprtcorner._x,uprtcorner._y);
                addPointToDataDigital(&img,&dd,dnrtcorner._x,dnrtcorner._y);
                if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
                if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
                if(processOneColumn(&dd, Q3, Q4, numQuestionCol2, 2)){INFPRINT("ERROR: Error in finding number circles.\n");algoTries++;continue;}
                deAllocData(&dd);
            }else if(numColumns==1){
                //SINGLE COLUMN
                addPointToDataDigital(&img,&dd,uplfcorner._x,uplfcorner._y);
                addPointToDataDigital(&img,&dd,dnlfcorner._x,dnlfcorner._y);
                addPointToDataDigital(&img,&dd,uprtcorner._x,uprtcorner._y);
                addPointToDataDigital(&img,&dd,dnrtcorner._x,dnrtcorner._y);
                if(allocData(&dd)==1){INFPRINT("ERROR: Error in allocating data for image buffer.\n");algoTries++;continue;}
                if(getDataFromBmp(&img,&dd)==1){INFPRINT("ERROR: Error in transferring data to image buffer.\n");algoTries++;continue;}
                printDataDigitalBuffer(&dd);
                if(processOneColumn(&dd, Q1, Q4, numQuestionCol1, 1)){INFPRINT("ERROR: Error in finding number circles.\n");algoTries++;continue;}
                deAllocData(&dd);
            }
            algoTries=3;
        }else if(algoTries==1){
            if(numColumns==2){
                //COL1
                if(processOneColumn(&dd, Q1, Q2, numQuestionCol1, 1)){INFPRINT("ERROR: Error in finding number circles.\n");algoTries++;continue;}
                //COL2
                if(processOneColumn(&dd, Q3, Q4, numQuestionCol2, 2)){INFPRINT("ERROR: Error in finding number circles.\n");algoTries++;continue;}
            }else if(numColumns==1){
                //SINGLE COLUMN
                if(processOneColumn(&dd, Q1, Q4, numQuestionCol1, 1)){INFPRINT("ERROR: Error in finding number circles.\n");algoTries++;continue;}
            }
            algoTries=3;
            deAllocData(&dd);
        }
        algoTries++;
    }//two tries
    if(algoTries==2){
        return 1;
    }
    return 0;
    cleanDataDigital(&dd);
    closeBmpImage(&img);

}

void processDir(char* path){
    int x,i;
    int len=strlen(path);
    if(len<=0){return;}
    if(path[len-1]!='\\'){strcat(path,"\\");}

    HANDLE hFind;
    BOOL bContinue = TRUE;
    WIN32_FIND_DATA data;
    char innerPath[MAXSTR];
    char basePath[MAXSTR];
    strcpy(basePath,path);
    strcat(path,"*.*");
    hFind = FindFirstFile(path, &data);

    while (hFind && bContinue) {
        // Check if this entry is a directory
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // This is a directory
            if(!strcmp(data.cFileName,".")){bContinue = FindNextFile(hFind, &data);continue;}
            if(!strcmp(data.cFileName,"..")){bContinue = FindNextFile(hFind, &data);continue;}

            strcpy(innerPath,basePath);
            strcat(innerPath,data.cFileName);
            processDir(innerPath);

        }else{
            if(!strcmp(data.cFileName,".")){bContinue = FindNextFile(hFind, &data);continue;}
            if(!strcmp(data.cFileName,"..")){bContinue = FindNextFile(hFind, &data);continue;}
            if(!strcmpi(data.cFileName,"thumbs.db")){bContinue = FindNextFile(hFind, &data);continue;}


            strcpy(innerPath,basePath);
            strcat(innerPath,data.cFileName);
            INFPRINT("\nProcessing: %s\n",data.cFileName);
            if(processOneFile(innerPath)==0){
                CSVPRINT("%s,OK",innerPath);
                if(numColumns==2){
                    i=0;
                    for(x=0;x<numQuestionCol1;x++){
                        CSVPRINT(",%d",ColumnAnswers1[x]);
                        if(ColumnAnswers1[x]<=5 && ColumnAnswers1[x]>=1){freqDatabase[i][ColumnAnswers1[x]-1]++;}
                        i++;
                    }
                    for(x=0;x<numQuestionCol2;x++){
                        CSVPRINT(",%d",ColumnAnswers2[x]);
                        if(ColumnAnswers2[x]<=5 && ColumnAnswers2[x]>=1){freqDatabase[i][ColumnAnswers2[x]-1]++;}
                        i++;
                    }
                }else{
                    i=0;
                    for(x=0;x<numQuestionCol1;x++){
                        CSVPRINT(",%d",ColumnAnswers1[x]);
                        if(ColumnAnswers1[x]<=5 && ColumnAnswers1[x]>=1){freqDatabase[i][ColumnAnswers1[x]-1]++;}
                        i++;
                    }
                }
                CSVPRINT("\n");
            }else{
                CSVPRINT("%s,FAILED 1\n",innerPath);
            }
            numOfResp++;
            //dito file
        }
        bContinue = FindNextFile(hFind, &data);
    }
    FindClose(hFind); // Free the dir structure
}


FILE* viewTemplates(){
    HANDLE hFind;
    BOOL bContinue = TRUE;
    WIN32_FIND_DATA data;
    FILE* tempTemplateForm = NULL;
    char str1[MAXSTR];

    INFPRINT("Form Type:\n");
    hFind = FindFirstFile("C:\\APRG\\SOOSA2014\\templates\\*.*", &data);
    int choice=1,ichoice=1;
    while (hFind && bContinue) {
        // Check if this entry is a directory
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // This is a directory
            if(!strcmp(data.cFileName,".")){bContinue = FindNextFile(hFind, &data);continue;}
            if(!strcmp(data.cFileName,"..")){bContinue = FindNextFile(hFind, &data);continue;}

        }else{
            INFPRINT("%d. %s\n",choice,data.cFileName);
            choice++;
        }
        bContinue = FindNextFile(hFind, &data);
    }
    INFPRINT("Enter selection: ");
    fgets(str1,MAXSTR,stdin);
    choice = atoi(str1);
    INFPRINT("Choice: %d\n",choice);
    FindClose(hFind); // Free the dir structure

    strcpy(str1,"C:\\APRG\\SOOSA2014\\templates\\");
    hFind = FindFirstFile("C:\\APRG\\SOOSA2014\\templates\\*.*", &data);
    bContinue = TRUE;
    ichoice=1;
    while (hFind && bContinue) {
        // Check if this entry is a directory
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // This is a directory
            if(!strcmp(data.cFileName,".")){bContinue = FindNextFile(hFind, &data);continue;}
            if(!strcmp(data.cFileName,"..")){bContinue = FindNextFile(hFind, &data);continue;}
        }else{
            if(choice==ichoice){
                strcat(str1,data.cFileName);
                if ((tempTemplateForm = fopen(str1, "r")) == NULL){
                    INFPRINT("ERROR: Error in reading template File.\n"); return NULL;
                }
                fgets(str1,MAXSTR,tempTemplateForm);
                fgets(str1,MAXSTR,tempTemplateForm);
                numColumns=atoi(str1);
                fgets(str1,MAXSTR,tempTemplateForm);
                numQuestionCol1=atoi(str1);
                fgets(str1,MAXSTR,tempTemplateForm);
                numQuestionCol2=atoi(str1);
                INFPRINT("Template Information: numColumns=%d numQuestionCol1=%d numQuestionCol2=%d.\n",numColumns,numQuestionCol1,numQuestionCol2);
                return tempTemplateForm;
            }
            ichoice++;
        }
        bContinue = FindNextFile(hFind, &data);
    }
    return NULL;
}

int main ( int argc, char *argv[] ) {
	Snapshot=NULL; csvfile=NULL;
#ifdef LOPFLAG
    if ((Snapshot = fopen("LogsAll.txt", "w")) == NULL){
        INFPRINT("ERROR: Error in Reading LOG File.\n"); return 1;
    }
#elif  DBGFLAG
    if ((Snapshot = fopen("LogsDBG.txt", "w")) == NULL){
        INFPRINT("ERROR: Error in Reading LOG File.\n"); return 1;
    }
#else
    if ((Snapshot = fopen("Logs.txt", "w")) == NULL){
        INFPRINT("ERROR: Error in Reading LOG File.\n"); return 1;
    }
#endif
    char str[MAXSTR];
    char AREA[MAXSTR];
    char PERIOD[MAXSTR];
    char DISCHARGE[MAXSTR];
    int len,x,i,j,total,median1,median2;
    FILE* basisHtml = NULL;
    FILE* outputHtml = NULL;
    FILE* templateForm = NULL;
    if(argc<2){return 1;}

    for(i=0; i<MAXQUESTIONSALL; i++){
        for(j=0; j<6; j++){
            freqDatabase[i][j]=0;
        }
    }

    INFPRINT("SOOSA2014 - Survey Output Optical Scan Analyzer\n\n");
    INFPRINT("AREA: ");
    fgets(AREA,MAXSTR,stdin);
    len=strlen(AREA); if(AREA[len-1]=='\n'){AREA[len-1]='\0';}
    INFPRINT("PERIOD: ");
    fgets(PERIOD,MAXSTR,stdin);
    len=strlen(PERIOD); if(PERIOD[len-1]=='\n'){PERIOD[len-1]='\0';}
    INFPRINT("DISCHARGE: ");
    fgets(DISCHARGE,MAXSTR,stdin);
    len=strlen(DISCHARGE); if(DISCHARGE[len-1]=='\n'){DISCHARGE[len-1]='\0';}
    strcpy(str,"PSS_Report_");
    strcat(str,AREA);
    strcat(str,"_");
    strcat(str,PERIOD);
    strcat(str,".csv");

    if ((csvfile = fopen(str, "w")) == NULL){
        INFPRINT("ERROR: Error in CSV File. %s\n",str); system("pause"); return 1;
    }
    strcpy(str,"PSS_Report_");
    strcat(str,AREA);
    strcat(str,"_");
    strcat(str,PERIOD);
    strcat(str,".html");

    if ((outputHtml = fopen(str, "w")) == NULL){
        INFPRINT("ERROR: Error in HTML File. %s\n",str); system("pause"); return 1;
    }
    //questionspecific

    numQuestionCol1=0;
    numQuestionCol2=0;
    numColumns=0;
    numOfResp=0;
    templateForm = viewTemplates();
    if(templateForm == NULL){
        INFPRINT("ERROR: Cannot find template.\n");return 1;
    }
    if(numQuestionCol1>MAXQUESTIONS){
        INFPRINT("ERROR: Maximum number of questions exceeded. There are %d questions (max=%d).\n",numQuestionCol1,MAXQUESTIONS);return 1;
    }
    if(numQuestionCol2>MAXQUESTIONS){
        INFPRINT("ERROR: Maximum number of questions exceeded. There are %d questions (max=%d).\n",numQuestionCol2,MAXQUESTIONS);return 1;
    }
    if(numColumns!=1 && numColumns!=2){
        INFPRINT("ERROR: Number of columns can be only 1 or 2. (numColumns=%d).\n",numColumns);return 1;
    }
    if(numColumns==1){
        numQuestionCol2=numQuestionCol1;//same number of question if numcolumns is 1
    }
    strcpy(str,argv[1]);
    len=strlen(str);
    if(len<=0){return 1;}
    CSVPRINT("FILE,STATUS");
    if(numColumns==2){
        for(x=0;x<numQuestionCol1;x++){CSVPRINT(",Col1_Q%d",x+1);}
        for(x=0;x<numQuestionCol2;x++){CSVPRINT(",Col2_Q%d",x+1);}
    }else{
        for(x=0;x<numQuestionCol1;x++){CSVPRINT(",Col1_Q%d",x+1);}
    }
    CSVPRINT("\n",str);
    if(str[len-1]=='\"'){
        str[len-1]='\0';
        INFPRINT("\nProcess Folder:%s\n",str);
        processDir(str);
    }else{
        INFPRINT("\nProcess File:%s\n",str);
        if(processOneFile(str)==0){
            CSVPRINT("%s,OK",str);
            if(numColumns==2){
                i=0;
                for(x=0;x<numQuestionCol1;x++){
                    CSVPRINT(",%d",ColumnAnswers1[x]);
                    if(ColumnAnswers1[x]<=5 && ColumnAnswers1[x]>=1){freqDatabase[i][ColumnAnswers1[x]-1]++;}
                    i++;
                }
                for(x=0;x<numQuestionCol2;x++){
                    CSVPRINT(",%d",ColumnAnswers2[x]);
                    if(ColumnAnswers2[x]<=5 && ColumnAnswers2[x]>=1){freqDatabase[i][ColumnAnswers2[x]-1]++;}
                    i++;
                }
            }else{
                i=0;
                for(x=0;x<numQuestionCol1;x++){
                    CSVPRINT(",%d",ColumnAnswers1[x]);
                    if(ColumnAnswers1[x]<=5 && ColumnAnswers1[x]>=1){freqDatabase[i][ColumnAnswers1[x]-1]++;}
                    i++;
                }
            }
            CSVPRINT("\n");
        }else{
            CSVPRINT("%s,FAILED 2\n",str);
        }
        numOfResp++;
    }

    if ((basisHtml = fopen("C:\\APRG\\SOOSA2014\\basis.html", "r")) == NULL){
        INFPRINT("ERROR: Error in basis.html file.\n"); return 1;
    }
    while(fgets(str,MAXSTR,basisHtml)!=NULL){
        if(str[0]=='@' && str[1]=='A' && str[2]=='A' && str[3]=='A' && str[4]=='@'){
            fprintf(outputHtml,"%s",AREA);
        }else if(str[0]=='@' && str[1]=='P' && str[2]=='P' && str[3]=='P' && str[4]=='@'){
            fprintf(outputHtml,"%s",PERIOD);
        }else if(str[0]=='@' && str[1]=='L' && str[2]=='L' && str[3]=='L' && str[4]=='@'){
            fprintf(outputHtml,"<h2>Number of Respondents: %d</h2>\n", numOfResp);
            fprintf(outputHtml,"<h2>Average Discharges per Month: %s</h2>\n", DISCHARGE);
            j=atoi(DISCHARGE);
            fprintf(outputHtml,"<h2>%% of Respondents to Discharges: %3.1lf%%</h2>\n", (double)numOfResp/j*100);
        }else if(str[0]=='@' && str[1]=='T' && str[2]=='T' && str[3]=='T' && str[4]=='@'){
            i=numQuestionCol1+numQuestionCol2;
            for(x=0;x<i;x++){
                fprintf(outputHtml,"<tr>\n");
        	    fgets(str,MAXSTR,templateForm);
        	    total = freqDatabase[x][0]+freqDatabase[x][1]+freqDatabase[x][2]+freqDatabase[x][3]+freqDatabase[x][4];
        	    if((total+1)%2==0){
                    median1 = (total+1)/2;
                    j=0;
                    while(median1>freqDatabase[x][j] && j<5){
                        median1 = median1-freqDatabase[x][j++];
                    }
                    median1=j+1+j+1;
        	    }else{
                    median1 = (total+1)/2;
                    median2 = median1+1;
                    j=0;
                    while(median1>freqDatabase[x][j] && j<5){
                        median1 = median1-freqDatabase[x][j++];
                    }
                    median1=j+1;
                    j=0;
                    while(median2>freqDatabase[x][j] && j<5){
                        median2 = median2-freqDatabase[x][j++];
                    }
                    median2=j+1;
                    median1=median1+median2;

        	    }
        	    if(x==i-1){
                    fprintf(outputHtml,"<td style=\"text-align:left;padding:3px\"><b>%s</b></td>\n",str);
        	    }else{
                    fprintf(outputHtml,"<td style=\"text-align:left;padding:3px\">%s</td>\n",str);
        	    }
                if(total==0){
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> 0.0%% </td>\n");
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> 0.0%% </td>\n");
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> 0.0%% </td>\n");
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> 0.0%% </td>\n");
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> 0.0%% </td>\n");
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> 0 </td>\n");
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> - </td>\n");
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\"> - </td>\n");
                }else{
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%3.1lf%%</td>\n",((double)freqDatabase[x][4])/total*100);
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%3.1lf%%</td>\n",((double)freqDatabase[x][3])/total*100);
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%3.1lf%%</td>\n",((double)freqDatabase[x][2])/total*100);
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%3.1lf%%</td>\n",((double)freqDatabase[x][1])/total*100);
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%3.1lf%%</td>\n",((double)freqDatabase[x][0])/total*100);
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%d</td>\n",total);
                    if(median1%2==0){
                        fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%d</td>\n",(median1/2));
                    }else{
                        fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%1.1lf</td>\n",((double)median1)/2);
                    }
                    fprintf(outputHtml,"<td style=\"text-align:center;padding:3px\">%3.1lf%%</td>\n",((double)freqDatabase[x][4]+freqDatabase[x][3]+freqDatabase[x][2])/total*100);
                }fprintf(outputHtml,"</tr>\n");
            }
        }else{
            fprintf(outputHtml,"%s",str);
        }
    }

    fclose(templateForm);
    fclose(outputHtml);
    fclose(csvfile);
#ifdef LOPFLAG
    fclose(Snapshot);
#elif  DBGFLAG
    fclose(Snapshot);
#else
    fclose(Snapshot);
#endif
    system("pause");
}

