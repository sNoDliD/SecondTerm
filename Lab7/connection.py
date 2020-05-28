from Scripts.Resources import Bot
from Scripts.Classes import Update, User
from Scripts.Handlers import update_handler

last_update_id = None
bot = Bot()


# todo 1) remove buntton for students, send link
#      2) ref link for techer, 'teacher' action
#      3) teacher and headman menu

def main():
    global last_update_id

    while True:
        update = bot.get_updates(last_update_id)
        if update:
            # print(update)
            # bot.send_message(User(738016227), '<a href="https://t.me/LabCSC_Bot?start=test_message">%s</a>' % 'link')
            update = Update(**update[0])
            last_update_id = update.id + 1

            update_handler(update) if update.chat_id > 0 else bot.leave_chat(update.chat_id)


if __name__ == '__main__':
    main()










