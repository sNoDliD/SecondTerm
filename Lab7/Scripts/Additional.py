from DataBase.DataBaseWork import get_query
from Scripts.Classes import Markup, button

all_groups = {}

for data in get_query('SELECT id, name, teacher_id, headman_id FROM groups ORDER BY name DESC;'):
    all_groups[data[0]] = data

#
# def get_group_name(group_id):
#     group_id = int(group_id)
#     data = tuple(map(lambda x: x[1], (i for i in _all_groups if i[0] == group_id)))
#     return data[0]




def yes_no_markup(callback, data=''):
    if data:
        data = '=' + '='.join(map(str, data))
    markup = Markup([button('✅', 'ans=%s=yes%s' % (callback, data)),
                     button('❎', 'ans=%s=no%s' % (callback, data))],
                    row_count=2)

    return markup


def get_info(bot, user_id):
    chat = bot.get_chat(user_id)
    result = chat['first_name']
    if 'second_name' in chat:
        result += ' %s' % chat['second_name']
    if 'username' in chat:
        result += ' (%s)' % chat['username']

    return '<a href="tg://user?id=%d">%s</a>' % (user_id, result)
