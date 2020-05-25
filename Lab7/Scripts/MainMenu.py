from Scripts.Resources import Bot
from Scripts.Classes import Markup, button
bot = Bot()


def send_student_menu(student, message_id=None):
    markup = Markup([button('Выбрать выриант', '1'), button('Мои задания', '2'), button('Дополнинельное', '3')])
    bot.edit_message(student, message_id, 'Выбери действие', markup)



