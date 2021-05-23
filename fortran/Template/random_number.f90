program main

    integer i
    real rand
 
    !** create random number ****************************************
    integer :: seedsize, j
    integer, allocatable :: seed(:)
    
    call random_seed(size = seedsize)       !初期値のサイズを取得
    allocate(seed(seedsize))                !配列の割り当て
    do j = 1, seedsize
        call system_clock(count = seed(j))  !時間を取得
    end do
    call random_seed(put = seed(:))         !初期値を与える
    !*****************************************************************
    
    do i = 1 , 10
    call random_number(rand)    
    write(6,*) rand
    end do

end program