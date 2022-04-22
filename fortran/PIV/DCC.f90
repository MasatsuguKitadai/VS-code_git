C  FORTRAN program dcc.f
C  Digital Cross-Correlation Method in 2D (sub-pixel version)
C  [2004.1.22 revised] 
C  Measured at each small floating object
C  M=11, MZ=512*480 ,mg(i)=33, mg(j)=33, m=2**l

      parameter( m=33,   l=25,    mx=512,    my=480 ) 
      parameter( dtime=0.004, spresol=0.316E-3 )

      integer*1 sc1(mx,my),sc2(mx,my),sc3(mx,my)
      integer ixtr(2000),iytr(2000)
      real s1r(m,m),s2r(m,m),dr(l,l),uft(2000),vft(2000)

      character a1*1,a3*2,a4*2,a5*4
      character*11 a1st,a2nd
      character*1 a2(0:9)
      data(a2(i),i=0,9)/'0','1','2','3','4','5','6','7','8','9'/

      a1='F'
      a3='G1'
      a4='G2'
      a5='.RAW'

      write(6,*) '���s�J�n!'
      write(6,*) 

      write(6,*) '����������͉摜�g���i�Q���P�g�j�H'
      read(5,*) nmax

      write(6,*) '�Q�l����臒l�H(0-255, Ex.120)'
      read(5,*) sc1th
c     sc1th=120.

      pi=4*atan(1.)

      write(6,230) '�񖇂̉摜�̎B�e���ԊԊu�@= ',dtime
      write(6,*)
  230 format(a,f5.4)
  220 format(a,i3,a,i3,a,i3)

C OPEN OUTPUT FILES
      open(3,file='velvec.dat',status='unknown')

      npall=0

      do 10 n=0,nmax-1

      write(6,*)
      write(6,*) 'Test Number',n

      n0=n
      n1=int(n0*0.001+0.00001)
      n2=int((n0-n1*1000)*0.01+0.00001)
      n3=int((n0-n1*1000-n2*100)*0.1+0.00001)
      n4=n0-n1*1000-n2*100-n3*10

      a1st=a1//a2(n1)//a2(n2)//a2(n3)//a2(n4)//a3//a5
      a2nd=a1//a2(n1)//a2(n2)//a2(n3)//a2(n4)//a4//a5

      write(6,*) '���̓t�@�C�����@',a1st,' & ',a2nd

C SCREEN TRACER
      call STvideo(mx,my,a1st,a2nd,sc1,sc2)

C FT METHOD (Operation E)
      write(6,*) '�摜��͊J�n' 

      call binlabel(m,l,mx,my,sc1,sc3,npmax,ixtr,iytr,sc1th)
      write(6,*) '���x�v���_���@',npmax

      do 300 np=1,npmax
        icn=ixtr(np)
        jcn=iytr(np)
        call DCC(m,l,mx,my,icn,jcn,sc1,sc2,s1r,s2r,dr,xshift,yshift)
        uft(np)=xshift
        vft(np)=yshift
  300 continue 
      write(6,*) '�摜��͏I��'
      call MakeFileEV2(npmax,ixtr,iytr,spresol,uft,vft)
      npall=npall+npmax

   10 continue

      close(3)
      close(7)

      write(6,*)
      write(6,*) '���o�x�N�g�������@',npall
      write(6,*)
      write(6,*) '�I��!' 
      stop
      end
C-----------------------------------------------------------------

      subroutine STvideo(mx,my,a1st,a2nd,sc1,sc2)
      integer*1 sc1(mx,my),sc2(mx,my)
      character*11 a1st,a2nd
      write(6,*) '�摜�t�@�C�����͊J�n'
      open(1,file=a1st,status='old',access='sequential',
     &form='unformatted',recordtype='fixed')
      open(2,file=a2nd,status='old',access='sequential',
     &form='unformatted',recordtype='fixed')
      read(1) ((sc1(i,j),i=1,mx),j=my,1,-1)
      read(2) ((sc2(i,j),i=1,mx),j=my,1,-1)
      close(1)
      close(2)
      write(6,*) '�摜�t�@�C�����͏I��'
      return
      end
C-----------------------------------------------------------------
      subroutine binlabel(m,l,mx,my,sc1,sc3,npmax,ixtr,iytr,sc1th)
      integer*1 sc1(mx,my),sc3(mx,my)
      integer ixtr(2000),iytr(2000)

C Binarization
      do 10 i=1,mx
        do 10 j=1,my
          sc1dum=sc1(i,j)
          if(sc1dum.lt.0.) sc1dum=sc1dum+256.
          if(sc1dum.ge.sc1th) then
            sc3(i,j)=0
           else
            sc3(i,j)=1
          end if
          if(i.eq.1.or.i.eq.mx.or.j.eq.1.or.j.eq.my) then
            sc3(i,j)=0
          end if
   10 continue

C Labeling

      do 20 i=2,mx-1
        do 20 j=2,my-1
          is41=sc3(i+1,j)+sc3(i-1,j)
          is42=sc3(i,j+1)+sc3(i,j-1)
          is81=sc3(i+1,j+1)+sc3(i-1,j-1)
          is82=sc3(i+1,j-1)+sc3(i-1,j+1)
          is=is41+is42+is81+is82
          if(sc3(i,j).eq.1.and.is.eq.0) sc3(i,j)=0
   20 continue

      lomit=int(float(m)*0.5)+int(float(l)*0.5)+2
      npmax=0
      do 30 i=2,mx-1
        do 30 j=2,my-1
          if(sc3(i,j).eq.1) then
            i0=i
            j0=j
   50       continue
            i1=i0-1
            j1=j0+1
            if(sc3(i1,j1).eq.1) goto 40
            i1=i0
            j1=j0+1
            if(sc3(i1,j1).eq.1) goto 40
            i1=i0+1
            j1=j0+1
            if(sc3(i1,j1).eq.1) goto 40
            i1=i0+1
            j1=j0
            if(sc3(i1,j1).eq.1) goto 40
            i1=i0+1
            j1=j0-1
            if(sc3(i1,j1).eq.1) goto 40
            i1=i0
            j1=j0-1
            if(sc3(i1,j1).eq.1) goto 40
            i1=i0-1
            j1=j0-1
            if(sc3(i1,j1).eq.1) goto 40
            i1=i0-1
            j1=j0
            if(sc3(i1,j1).eq.1) goto 40
            if(i0.ge.lomit.and.i0.le.mx-lomit+1.and.
     &         j0.ge.lomit.and.j0.le.my-lomit+1) then
            npmax=npmax+1
            ixtr(npmax)=i0
            iytr(npmax)=j0
            end if
            sc3(i0,j0)=0
            goto 60
   40       continue
            sc3(i0,j0)=0
            i0=i1
            j0=j1
            goto 50
   60     continue
          end if
   30 continue

      return
      end

C-----------------------------------------------------------
      subroutine DCC(m,l,mx,my,ic,jc,sc1,sc2,s1r,s2r,dr,xshift,yshift)
      integer*1 sc1(mx,my),sc2(mx,my)
      real s1r(m,m),s2r(m,m),dr(l,l)

      xc=float(ic)-0.5
      yc=float(jc)-0.5
      ic2=ic
      jc2=jc
      mhalf=int(float(m)*0.5)+1
      lhalf=int(float(l)*0.5)

      do 10 i=1,m
        do 10 j=1,m
          s1r(i,j)=sc1(ic+i-mhalf,jc+j-mhalf)
          if(s1r(i,j).lt.0.) s1r(i,j)=s1r(i,j)+256.
   10 continue

      do 30 ishift=-lhalf,lhalf
        do 30 jshift=-lhalf,lhalf
          do 20 i=1,m
            do 20 j=1,m
              if(ic2+ishift+i-mhalf.gt.mx-1) write(6,*) 'i over'
              if(ic2+ishift+i-mhalf.lt.0) write(6,*) 'i below'
              if(jc2+jshift+j-mhalf.gt.my-1) write(6,*) 'j over'
              if(jc2+jshift+j-mhalf.lt.0) write(6,*) 'j below'
              s2r(i,j)=sc2(ic2+ishift+i-mhalf,jc2+jshift+j-mhalf)
              if(s2r(i,j).lt.0.) s2r(i,j)=s2r(i,j)+256.
   20     continue
          call cross(m,s1r,s2r,cc)
          dr(ishift+lhalf+1,jshift+lhalf+1)=cc
   30 continue
c     write(6,*) 'Cross completed'
      call findpeak(l,dr,val,xshift,yshift)
c     write(6,*) 'Findpeak completed'

      return
      end
C--------------------------------------------------------------
      subroutine cross(m,s1r,s2r,cc)
      real s1r(m,m),s2r(m,m)

      s1rm=0.
      s2rm=0.
      do 10 i=1,m
        do 10 j=1,m
          s1rm=s1rm+s1r(i,j)
          s2rm=s2rm+s2r(i,j)
   10 continue
      s1rm=s1rm/float(m*m)
      s2rm=s2rm/float(m*m)

      s11=0.
      s12=0.
      s22=0.
      do 20 i=1,m
        do 20 j=1,m
          s1r(i,j)=s1r(i,j)-s1rm
          s2r(i,j)=s2r(i,j)-s2rm
          s11=s11+s1r(i,j)*s1r(i,j)
          s12=s12+s1r(i,j)*s2r(i,j)
          s22=s22+s2r(i,j)*s2r(i,j)
   20 continue
      
      if(sqrt(s11*s22).le.1.e-6) then
        cc=0.
       else
        cc=s12/sqrt(s11*s22)
      end if

      cc=0.5*(cc+1.)

      return
      end
C-----------------------------------------------------------------
      subroutine findPeak(l,dr,val,xshift,yshift)
      real dr(l,l),val
      icenter=int(0.5*l)+1
      jcenter=icenter
      ip=2
      jp=2
      val=dr(ip,jp)
      do 10 i=2,l-1
        do 10 j=2,l-1
          if(dr(i,j).gt.val) then 
            val=dr(i,j)
            ip=i
            jp=j
          endif
   10 continue
c      write(6,*) ip,jp
c      write(6,*) dr(ip+1,jp),dr(ip,jp),dr(ip-1,jp)
c      write(6,*) dr(ip,jp+1),dr(ip,jp),dr(ip,jp-1)
c      xshift=float(ip-icenter)
c      yshift=float(jp-jcenter)
c      write(6,*) xshift,yshift
c      return
      f1=log(dr(ip+1,jp))
      f2=log(dr(ip,jp))
      f3=log(dr(ip-1,jp))
      xsubpix=-0.5*(f1-f3)/(f1-2.*f2+f3)
      f1=log(dr(ip,jp+1))
      f2=log(dr(ip,jp))
      f3=log(dr(ip,jp-1))
      ysubpix=-0.5*(f1-f3)/(f1-2.*f2+f3)
      xshift=float(ip-icenter)+xsubpix
      yshift=float(jp-jcenter)+ysubpix
      return
      end 
C-----------------------------------------------------------------  
      subroutine MakeFileEV2(npmax,ixtr,iytr,spresol,uft,vft)
      real uft(2000),vft(2000)
      integer ixtr(2000),iytr(2000)
      write(6,*) '���x�x�N�g���o�͊J�n'
      do 30 np=1,npmax
        xp=spresol*(ixtr(np)-1)
        yp=spresol*(iytr(np)-1)
        write(3,*) xp,yp,spresol*uft(np),spresol*vft(np)
   30 continue
      write(6,*) '���x�x�N�g���o�͏I��'
      return
      end
