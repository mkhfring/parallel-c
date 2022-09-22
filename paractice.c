int main(int argc, char const *argv[])
{
    /* code */
#pragma omp parallel num_threads(2)
{
#pragma omp task
printf("A");
#pragma omp task
printf("B");
}
    return 0;
}

