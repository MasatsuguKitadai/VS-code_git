C  FORTRAN program convert.f
C
C  This program is for converting raw image files to bitmaps.
C  The first raw file should be converted to a bitmap file 
C  using INSPECTOR (Important!).
C  The conversion from BMP's to GIF's can be sequentially performed 
C  with PMVIEW on OS/2, and then GIF amination can be constructed 
C  from the resulting GIF's using WebAnimation on Win98.
C  [2000.10.5] :  revised [2004.1.22]

      parameter(mx=512,my=480) 
      integer*1 sc1(mx,my),dum(1078)
      character a1*1,a3*2,a4*2,a5*4,a6*4
      character*12 ainput,aoutput
      character*1 a2(0:9)
      data(a2(i),i=0,9)/'0','1','2','3','4','5','6','7','8','9'/

      a1='F'
      a3='G1'
      a4='G2'
      a5='.RAW'
      a6='.BMP'

      write(6,*) '実行開始!'
      write(6,*) 

      write(6,*) '処理画像組数？'
      read(5,*) nmax
      write(6,*) '最初の処理画像組番号？'
      read(5,*) nstart
c      write(6,*) 'ヘッダ部のサイズ？ (Ex. 1078)'
c      read(5,*) lhead
      lhead=1078

      open(4,file='512480.bmp',status='old',access='sequential',
     & form='unformatted',recordtype='fixed')
      read(4) (dum(i0),i0=1,lhead)
      close(4)


      do 10 n=nstart,nstart+nmax-1

      write(6,*)
      write(6,*) 'Test Number',n

      n0=n
      n1=int(n0*0.001+0.0001)
      n2=int((n0-n1*1000)*0.01+0.0001)
      n3=int((n0-n1*1000-n2*100)*0.1+0.0001)
      n4=n0-n1*1000-n2*100-n3*10
      
      ainput =a1//a2(n1)//a2(n2)//a2(n3)//a2(n4)//a3//a5
      aoutput=a1//a2(n1)//a2(n2)//a2(n3)//a2(n4)//a3//a6

      write(6,*) 'Processing image file is ',ainput

      write(6,*) '画像ファイル入力開始'
      open(4,file=ainput,status='old',access='sequential',
     & form='unformatted',recordtype='fixed')
      open(2,file=aoutput,status='unknown',access='sequential',
     & form='unformatted',recordtype='fixed')
      read(4)  ((sc1(i,j),i=1,mx),j=1,my)
      write(2) (dum(i0),i0=1,lhead),((sc1(i,j),i=1,mx),j=my,1,-1)
      close(4)
      close(2)
      write(6,*) '画像ファイル出力終了'

      ainput =a1//a2(n1)//a2(n2)//a2(n3)//a2(n4)//a4//a5
      aoutput=a1//a2(n1)//a2(n2)//a2(n3)//a2(n4)//a4//a6

      write(6,*) 'Processing image file is ',ainput

      write(6,*) '画像ファイル入力開始'
      open(4,file=ainput,status='old',access='sequential',
     & form='unformatted',recordtype='fixed')
      open(2,file=aoutput,status='unknown',access='sequential',
     & form='unformatted',recordtype='fixed')
      read(4)  ((sc1(i,j),i=1,mx),j=1,my)
      write(2) (dum(i0),i0=1,lhead),((sc1(i,j),i=1,mx),j=my,1,-1)
      close(4)
      close(2)
      write(6,*) '画像ファイル出力終了'

   10 continue

      write(6,*)
      write(6,*) '終了!' 
      stop
      end
