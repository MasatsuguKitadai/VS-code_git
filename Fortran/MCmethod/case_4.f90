! Program Name : case_1.f90

program main
    implicit none
    integer, parameter :: num = 501 
    integer i
    real x, y, f, s1, s2, a, b, pi
    real r(num)
    real area(num)

    !** create random number *********************
    
    integer :: seedsize, j
    integer, allocatable :: seed(:)
    
    call random_seed(size = seedsize)       !初期値のサイズを取得
    allocate(seed(seedsize))                !配列の割り当て
    do j = 1, seedsize
        call system_clock(count = seed(j))  !時間を取得
    end do
    call random_seed(put = seed(:))         !初期値を与える
    
    !********************************************

    pi = 4.0 *atan(1.0)
    write(6,*)'pi = ',pi

    call random_number(r)

    do 10 i = 1 ,num
       ! write(6,*) r(i)
    10 continue

    s1 = 0
    s2 = 0

    do 20 i = 1, num - 1
        x = r(i)
        y = r(i + 1)
    !**************************
        f = sin(pi * x)
    !**************************
    if (f > y) then
        s1 = s1 + 1
    else if (f < y) then
        s2 = s2 + 1
    end if

    a = (s1 / (i + 1))
    b = (s2 / (i + 1))
    area(i) = a

    write(6,*) 'area[',i,'] = ',area(i)

    20 continue

    open(17, file = 'output/case_4.dat', status='replace')
    do 30 i = 1, num - 1
    write (17,*) i,area(i)
    30 continue
    close(17)

end program