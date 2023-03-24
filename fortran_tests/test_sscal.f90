! example.f90
program main
    implicit none (type, external)
    external :: sscal

    integer, parameter :: N = 10

    real :: x(N)
    real :: a

    x = [ 1., 2., 3., 4., 5., 6., 7., 8., 9., 10.]
    a = 2.1

    print '("x = a*x ")'
    print '("a = ", f0.1)', a 
    print '("X = [ ", 3(f0.1, " "), "]")', x

    call sscal(N, a, x, 1)

    print '(/, "X = a * X")'
    print '("X = [ ", 3(f0.1, " "), "]")', x
end program main
