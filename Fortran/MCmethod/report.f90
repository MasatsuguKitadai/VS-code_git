! Program Name : report.f90

program main

    implicit none
    integer, parameter :: num = 5000
    integer, parameter :: case = 5
    integer i, j, n
    real x, y, a, b, pi, f_1, f_2, f_3, f_4, f_5
    real f(case),s(case)
    real r(num + 1)
    real area(num + 1, case)
    real dif(num + 1, case)

    !** create random number *********************
    
    integer :: seedsize
    integer, allocatable :: seed(:)
    
    call random_seed(size = seedsize)       
    allocate(seed(seedsize))               
    do j = 1, seedsize
        call system_clock(count = seed(j)) 
    end do
    call random_seed(put = seed(:))         
    
    !********************************************

    pi = 4.0 *atan(1.0)
    ! write(6,*)'pi = ',pi

    call random_number(r)

    do 10 j = 1 ,case
       s(j) = 0
    10 continue

    open(17, file = 'result/result.dat', status='replace')

    do 20 i = 1, num
        x = r(i)
        y = r(i + 1)
    
        f(1) = x                  !case_1
        f(2) = x*x                !case_2
        f(3) = cos(pi / 2.0 * x)  !case_3
        f(4) = sin(pi * x)        !case_4
        f(5) = exp(-x * x)        !case_5

        do 100 j = 1, 5   
            if (f(j) > y) then
                s(j) = s(j) + 1
            end if    
            a = (s(j)/i)
            area(i,j) = a
        100 continue
        20 continue

do 30 i = 1, num
    write (17,*) i,area(i,1),area(i,2),area(i,3),area(i,4),area(i,5)
30 continue

close(17)

open(18, file= 'result/difference.dat', status='replace')

f_1 = 1.0/2.0
f_2 = 1.0/3.0
f_3 = 2.0/pi
f_4 = 2.0/pi
f_5 = 2.0

do 40 i = 1, num
    dif(i,1) = area(i,1) - f_1
    dif(i,2) = area(i,2) - f_2
    dif(i,3) = area(i,3) - f_3
    dif(i,4) = area(i,4) - f_4
    dif(i,5) = area(i,5) - f_5
40 continue

do 50 i = 1, num
    write (18,*) i,dif(i,1),dif(i,2),dif(i,3),dif(i,4),dif(i,5)
50 continue

close(18)

end program