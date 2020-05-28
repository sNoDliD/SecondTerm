from timeit import timeit

# x = timeit('"-".join(str(n) for n in range(10000))', number=1000)
# y = timeit('"-".join([str(n) for n in range(10000)])', number=1000)
# z = timeit('"-".join(map(str, range(10000)))', number=1000)       todo win

# x = timeit('''
# u = 100
# u = (u+u) if u == 10 else u*u
# ''', number=10000000)
# y = timeit('''
# u = 100
# if u == 10:
#     u = (u+u)
# else:
#     u = u*u
# ''', number=10000000)
#
#
# print(x, y)


# x = timeit('''
# class User:
#     __data = {}
#
#     def __new__(cls, user_id):
#         if user_id not in User.__data:
#             instance = super().__new__(cls)
#             instance.id = user_id
#             instance.group_id = 0
#             instance.name = ''
#             instance.status = 0
#             instance.last_markup = 0
#             instance.action = ''
#             User.__data[user_id] = instance
#
#         return User.__data[user_id]
# for i in range(100):
#     x = [User(i) for i in range(100)]
#
#
# ''', number=1000)
# y = timeit('''
# data = {}
# class User:
#     global data
#
#     def __new__(cls, user_id):
#         if user_id not in data:
#             instance = super().__new__(cls)
#             instance.id = user_id
#             instance.group_id = 0
#             instance.name = ''
#             instance.status = 0
#             instance.last_markup = 0
#             instance.action = ''
#             data[user_id] = instance
#
#         return data[user_id]
#
# for i in range(100):
#     x = [User(i) for i in range(100)]
#
# ''', number=1000)                     todo

t, z = 12, None
send = z or t
i = ('%d=%s' % (send, z is None))
u = i.split('=')[-1]
j = bool(u)
print(j)
import os

x = os.environ
print(type(x))