import random

def sjf_scheduling(jobs):
    # 根据作业长度（服务时间）对作业进行排序
    jobs.sort(key=lambda x: x[1])  # x[1]是作业的长度
    time = 0
    response_times = []

    for job in jobs:
        job_id, length = job
        response_times.append(time)  # 记录响应时间
        time += length  # 增加时间为作业长度

    return response_times

# 生成具有指定长度范围的作业
def generate_jobs(num_jobs, length_range):
    jobs = []
    for i in range(num_jobs):
        length = random.randint(length_range[0], length_range[1])  # 随机作业长度
        jobs.append((i, length))  # (job_id, job_length)
    return jobs

# 主模拟
num_jobs = 1000  # 作业数量
length_ranges = [(0, 10), (0, 30), (0, 100)]  # 长度范围
avg_response_times = []

# 进行10次模拟
for _ in range(10):
    jobs = generate_jobs(num_jobs, random.choice(length_ranges))  # 随机选择长度范围
    response_times = sjf_scheduling(jobs)
    average_response_time = sum(response_times) / len(response_times)
    avg_response_times.append(average_response_time)

print(avg_response_times)
