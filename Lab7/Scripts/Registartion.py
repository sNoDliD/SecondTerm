from Scripts.Resources import Bot, timer
from Scripts.Classes import Markup, button, User
from Scripts.Additional import all_groups, yes_no_markup, get_info
from Scripts.MainMenu import send_student_menu

from DataBase.DataBaseWork import get_query
bot = Bot()


def confirm_user(update, user, params):
    answer, student_id = params
    student = User(student_id)

    if answer == 'no':
        student.action = 'ban'
        bot.delete_message(user.id, update.message_id, 'Отказано')

    else:
        if answer == 'headman':
            get_query('UPDATE groups SET headman_id = ? WHERE id = ?;', values=(student_id, student.group_id))
            all_groups[student.group_id] = *all_groups[student.group_id][:-1], int(student_id)

        student.action = None
        send_student_menu(student)
        bot.delete_message(user.id, update.message_id, 'Принят')

    student.update()


def add_group_id(update, user, params):
    bot.answer_callback_query(update.query_id, 'Запрос на добавление в группу послан', True)
    bot.edit_message(user, update.message_id, 'Ожидай подтверждения ⏳')
    _, group_id, send_id, need_new_admin = params

    user.group_id = int(group_id)
    user.action = 'wait'
    user.update()

    markup = yes_no_markup('reg', (user.id, ))
    if need_new_admin == 'True':
        markup.row([button('Сделать старостой', 'ans=reg=headman=%d' % user.id)])
    text = '<pre>Подтвердите добавление </pre>\n%s %s\nВ группу <b>%s</b>' % (get_info(bot, user.id), user.name,
                                                                              all_groups[user.group_id][1])
    bot.send_message(User(send_id), text, markup, clear_markup=False)


def first_message(user):
    bot.send_message(user, 'Пришли свою фамилию')
    user.action = 'registration'
    user.update()


def choose_group(user):
    markup = Markup()

    for group_id, name, teacher_id, headman_id in all_groups.values():
        markup.add([button(name, 'g_id=%d=%d=%s' % (group_id, headman_id or teacher_id, headman_id is None))])

    bot.send_message(user, 'Выбери свою группу', markup)


def registration(update, user):
    if not user.name:
        if not update.text:
            bot.send_message(user, 'Мне нужна твоя фамилия...')
        else:
            user.name = str(update.text)[:15].capitalize()

            if user.update() is Exception:
                bot.send_message(user, 'Эта фамилия уже занята. Отправь мне свою')
                user.name = None

            else:
                choose_group(user)

    else:
        choose_group(user)
