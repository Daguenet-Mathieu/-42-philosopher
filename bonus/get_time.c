t_ull   get_time()
{
    t_time;
    
    gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}