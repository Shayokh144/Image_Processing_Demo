#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<algorithm>

using namespace std;
using namespace cv;


void GaussianBlur()
{
    Mat kg,src;
    int mask;
    cout<<"enter mask="<<"\n";
    cin>>mask;
    double gs , sd,rval;
    double kk=0;
    int col,row,type;
    int bd=mask/2;
    src = imread("ben2.png", 0);
    copyMakeBorder( src,  kg, bd, bd, bd, bd, BORDER_CONSTANT,0);

    col=src.cols;
    row=src.rows;
    type=src.type();
    Mat output( row, col, type, Scalar(0, 0, 0));
    imshow("Main image ", src);

    waitKey(0);

    cout<<"sd="<<"\n";
    cin>>sd;


    int xx,yy;


    for(int i=0; i<src.rows; i++)
    {

        for(int j=0; j<src.cols; j++)
        {

            xx=(-1)*(bd);

            for(int x=i; x<i+mask; x++)
            {
                yy=(-1)*(bd);
                for(int y=j; y<j+mask; y++)
                {


                    gs= exp(-(((xx*xx)+(yy*yy))/(2*(sd*sd))));
                    gs=gs/(2*3.1416*sd*sd);
                    //	cout<<gs<<"\n";
                    rval=kg.at<uchar>(x,y);
                    gs=gs*rval;
                    kk=kk+gs;

                    //cout<<kk<<"\n";
                    //cout<<"xx="<<xx<<"yy="<<yy<<"\n";


                    //sum=sum+gs;
                    yy++;
                }
                xx++;
            }
            //int yy=dst.at<uchar>(i,j);
            //cout<<"yy="<<yy;

//	break;
            int u=(int)kk;
            //u=u+1;
            output.at<uchar>(i,j) = uchar(u);
            kk=0;


        }
//break;
    }

    int z;


    imshow("Gaussian Blurr image ", output);
    waitKey(0);



}



void Median()
{




    Mat dst,src,bsrc,kg;
    vector<int>v;
    int a,mask,bd,col,row,type,idx;
    cout<<"enter mask\n";
    cin>>mask;
    src = imread("Lenna_gray_noisy.jpg", 0);

    bd=mask/2;

    copyMakeBorder( src,  bsrc, bd, bd, bd, bd, BORDER_CONSTANT,0 );
    col=src.cols;
    row=src.rows;
    type=src.type();
    Mat output( row, col, type, Scalar(0, 0, 0));


    imshow("Bordered image ", bsrc);
    waitKey(0);

    int val=255;

    for(int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {

            for(int x=i; x<i+mask; x++)
            {

                for(int y=j; y<j+mask; y++)
                {






                    int val=bsrc.at<uchar>(x,y);



                    v.push_back(val);
                    //cout<<val<<" ";
                }
            }
            sort(v.begin(),v.end());
            idx=v.size()/2;
            a=v[idx];

            output.at<uchar>(i,j) = uchar(a);

            v.clear();

            //break;

        }
//break;
    }


    imshow("Output image ", output);
    waitKey(0);



}


void Roberts(Mat src)
{

    int roberts[10];

    Mat bsrc;

    int a,mask,bd,ss,col,row,type;
    mask=3;


    bd=mask/2;

    copyMakeBorder( src,  bsrc, bd, bd, bd, bd, BORDER_CONSTANT,0 );
    col=src.cols;
    row=src.rows;
    type=src.type();
    Mat output( row, col, type, Scalar(0, 0, 0));


    imshow("Main image ", src);
    waitKey(0);

    int val=255;
    int sum1;
    int avg=1;
//cout<<src.rows<<"  cc  "<<src.cols;


//.................Roberts......................
    int idx;

    for(int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {

            sum1=0;
            idx=1;

            for(int x=i; x<i+mask; x++)
            {

                for(int y=j; y<j+mask; y++)
                {





                    val=bsrc.at<uchar>(x,y);
                    roberts[idx]=val;

                    idx++;


                }
            }


            int gx,gy,delf;
            gx=roberts[9] - roberts[5];
            gy=roberts[8] - roberts[6];
            delf=sqrt(gx*gx+gy*gy);
            if(delf>255)
                delf=255;

            output.at<uchar>(i,j) = uchar(delf);




        }

    }


////.........................output............................/////////////




    imshow("Roberts image ", output);
    waitKey(0);




}







void MaxMin(Mat src,int choice)
{


    Mat bsrc;

    int mask,border,col,row,type;
    cout<<"enter mask\n";
    cin>>mask;


    border=mask/2;

    copyMakeBorder( src,  bsrc, border, border, border, border, BORDER_CONSTANT,0 );
    col=src.cols;
    row=src.rows;
    type=src.type();
    Mat output( row, col, type, Scalar(0, 0, 0));




    imshow("Main image ", src);
    waitKey(0);

    int val=255;
    int mxmn;




//..................................
    int idx;

    for(int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {
            if(choice==2)

                mxmn=0;
            else
                mxmn=9999;

            for(int x=i; x<i+mask; x++)
            {

                for(int y=j; y<j+mask; y++)
                {




//		yy++;
                    val=bsrc.at<uchar>(x,y);


                    if(choice==2)
                    {

                        if(val>mxmn)
                            mxmn=val;

                    }

                    else

                    {

                        if(val<mxmn)
                            mxmn=val;
                    }
                }
            }



            output.at<uchar>(i,j) = uchar(mxmn);




        }
//break;
    }

//cout<<mxmn<<"\n";




    if(choice==2)
        imshow("Max image ", output);
    else
        imshow("Min image ", output);
    waitKey(0);




}

void Prewitts(Mat src)
{

    int prewitts[10];

    Mat bsrc;

    int mask,border,col,row,type;
    mask=3;
    // src = imread("p.png", 0);

    border=mask/2;

    copyMakeBorder( src,  bsrc, border, border, border, border, BORDER_CONSTANT,0 );
    col=src.cols;
    row=src.rows;
    type=src.type();
    Mat output( row, col, type, Scalar(0, 0, 0));


    imshow("Main image ", src);
    waitKey(0);

    int val=255;
    int sum1;



    int id=0;

    for(int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {

            sum1=0;
            id=1;

            for(int x=i; x<i+mask; x++)
            {

                for(int y=j; y<j+mask; y++)
                {




                    val=bsrc.at<uchar>(x,y);
                    prewitts[id]=val;

                    id++;


                }
            }


            int gx,gy,delf;
            gx=(prewitts[3]+prewitts[6]+prewitts[9] )-(prewitts[1]+prewitts[4]+prewitts[7]);
            gy=(prewitts[3]+prewitts[1]+prewitts[2] )-(prewitts[7]+prewitts[8]+prewitts[9]);

            //gx=(prewitts[3]+prewitts[2]+prewitts[1] )-(prewitts[7]+prewitts[8]+prewitts[9]);
            //gy=(prewitts[4]+prewitts[1]+prewitts[7] )-(prewitts[3]+prewitts[6]+prewitts[9]);
            delf=sqrt(gx*gx+gy*gy);
            //delf=gx;
            if(delf>255)
                delf=255;

            output.at<uchar>(i,j) = uchar(delf);



        }

    }


////.........................output............................/////////////



    imshow("Prewitts image ", output);
    waitKey(0);





}



Mat Dial(Mat src,int structure[3][3],int cx,int cy)
{

    Mat bsrc;
    int a,mask,bd,ss,col,row,type;
    mask=3;
    cx++;
    cy++;

    bd=mask/2;

    copyMakeBorder( src,  bsrc, bd, bd, bd, bd, BORDER_CONSTANT,0 );
    col=src.cols;
    row=src.rows;
    type=src.type();


    Mat output( row, col, type, Scalar(0, 0, 0));


    // imshow("Main image ", src);
    // waitKey(0);
    int gx,gy,delf;

    int val=255;
    int sum1;
    int avg=1;

    int idx;
    int count=0;


    {

        for(int i=0; i<src.rows; i++)
        {
            for(int j=0; j<src.cols; j++)
            {


                idx=0;

                gx=0;
                for(int x=i+mask-1; x>=i; x--)
                {
                    gy=0;
                    val=0;
                    for(int y=j+mask-1; y>=j; y--)
                    {



                        val=bsrc.at<uchar>(x,y);

                        if(val==structure[gx][gy])
                        {
                            idx++;
                        }
                        gy++;



                    }
                    gx++;
                }
                //cout<<"idx="<<idx<<"\n";
                if(idx>=1)
                {
                    //cout<<"dd";
                    output.at<uchar>(i,j) = uchar(structure[cx][cy]);
                }
                else

                {
                    output.at<uchar>(i,j) = uchar(0);
                }
                idx=0;



            }

        }






    }



    return output;

}











Mat Erosion(Mat src,int structure[3][3],int cx,int cy)
{

    Mat bsrc;
    int a,mask,bd,ss,col,row,type;
    mask=3;
    cx++;
    cy++;

    bd=mask/2;

    copyMakeBorder( src,  bsrc, bd, bd, bd, bd, BORDER_CONSTANT,0 );
    col=src.cols;
    row=src.rows;
    type=src.type();


    Mat output( row, col, type, Scalar(0, 0, 0));



    int gx,gy,delf;

    int val=255;
    int sum1;
    int avg=1;

    int idx;
    int count=0;


    {

        for(int i=0; i<src.rows; i++)
        {
            for(int j=0; j<src.cols; j++)
            {


                idx=0;

                gx=0;
                for(int x=i; x<i+mask; x++)
                {
                    gy=0;
                    val=0;
                    for(int y=j; y<j+mask; y++)
                    {



                        val=bsrc.at<uchar>(x,y);

                        if(val==structure[gx][gy])
                        {
                            idx++;
                        }
                        gy++;



                    }
                    gx++;
                }
                //cout<<"idx="<<idx<<"\n";
                if(idx==9)
                {
                    //cout<<"dd";
                    output.at<uchar>(i,j) = uchar(structure[cx][cy]);
                }
                else
                {
                    output.at<uchar>(i,j) = uchar(0);
                }


                idx=0;



            }

        }


    }


    return output;


}




Mat Boundary(Mat src,Mat erod)
{
    int erv,srv;

    for(int i=0; i<src.rows; i++)
    {
        for(int j=0; j<src.cols; j++)
        {
            srv=src.at<uchar>(i,j);
            erv=erod.at<uchar>(i,j);
            //	  cout<<srv<<"   "<<erv<<"\n";

            if(srv==erv)
            {
                src.at<uchar>(i,j) = uchar(0);

            }
        }


    }

    return src;
}





int main( )
{
    int choice;
    cout<<"Enter\n1 for  Roberts\n2 for Max\n3 for Min\n4 for  Prewitts\n5 for Median \n6 for Gaussian\n17 for Erosion\n18 for Dilation\n7 for opening\n8 for closing\n9 for boundary\n";

    // cout<<"Enter 7 for Opening\n8 for Closing\n9 for Boundary   ";



    cin>>choice;

    Mat src = imread("per.png", 0);

    if(choice==1)
    {

        Roberts(src);



    }



    else if(choice==2||choice==3)
    {

        MaxMin(src,choice);

    }

    else if(choice==4)
    {

        Prewitts(src);

    }

    else if(choice==5)
    {

        Median();

    }

    else if(choice==6)
    {


        GaussianBlur();

    }


    else if(choice==17)
    {
        Mat esrc= imread("abc.tif", 0);
        int structure[3][3];
        int cx,cy;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {

                structure[i][j]=255;


            }

        }
        cout<<"center:"<<"\n";
        cin>>cx>>cy;



        Mat rec=  Erosion(esrc,structure,cx,cy);
        imshow("output image ", rec);
        waitKey(0);

    }

    else if (choice==18)

    {

        Mat esrc= imread("abc.tif", 0);
        Mat rec;
        int structure[3][3];
        int cx,cy;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {

                structure[i][j]=255;


            }

        }
        cout<<"center:"<<"\n";
        cin>>cx>>cy;

        rec= Dial(esrc,structure,cx,cy);

        imshow("output image ", rec);
        waitKey(0);

    }



    else if (choice==7)

    {

        Mat esrc= imread("abc.tif", 0);

        Mat rec1,rec2;
        int structure[3][3];
        int cx,cy;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {

                structure[i][j]=255;


            }

        }
        cout<<"center:"<<"\n";
        cin>>cx>>cy;
        imshow("Main image ", esrc);
        waitKey(0);

        rec1=  Erosion(esrc,structure,cx,cy);

        rec2= Dial(rec1,structure,cx,cy);

        imshow("Opening image ", rec2);
        waitKey(0);

    }


    else if (choice==8)

    {

        Mat esrc= imread("abc.tif", 0);

        Mat rec1,rec2;
        int structure[3][3];
        int cx,cy;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {

                structure[i][j]=255;


            }

        }
        cout<<"center:"<<"\n";
        cin>>cx>>cy;
        imshow("Main image ", esrc);
        waitKey(0);

        rec1=  Dial(esrc,structure,cx,cy);

        rec2= Erosion(rec1,structure,cx,cy);

        imshow("Closing image ", rec2);
        waitKey(0);

    }


    else if (choice==9)
    {

        Mat esrc= imread("Picture1.png", 0);

        Mat rec1,rec2;
        int structure[3][3];
        int cx,cy;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {

                structure[i][j]=255;


            }

        }
        cout<<"center:"<<"\n";
        cin>>cx>>cy;
        imshow("Main image ", esrc);
        waitKey(0);

        rec1=  Erosion(esrc,structure,cx,cy);
        imshow("RRR image ", rec1);
        waitKey(0);

        Mat Bound=Boundary(esrc,rec1);

        imshow("Bound image ", Bound);
        waitKey(0);






    }









}
