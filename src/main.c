int main(void)
{
    char hello[] = "hello world.";
    int hello_size = sizeof(hello) / sizeof(hello[0]);

    return hello_size;
}
