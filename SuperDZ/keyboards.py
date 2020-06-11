from aiogram.types import ReplyKeyboardRemove, \
	ReplyKeyboardMarkup, KeyboardButton, \
	InlineKeyboardMarkup, InlineKeyboardButton

button_1hour = InlineKeyboardButton(text = '1 час', callback_data = '1hour')
button_2hour = InlineKeyboardButton(text = '2 часа', callback_data = '2hour')
button_3hour = InlineKeyboardButton(text = '3 часа', callback_data = '3hour')
button_other = InlineKeyboardButton(text = 'Другое', callback_data = 'other')

hours = InlineKeyboardMarkup()
hours.add(button_1hour)
hours.add(button_2hour)
hours.add(button_3hour)
hours.add(button_other)

button_minutes = InlineKeyboardButton(text = 'Минут(ы)', callback_data = 'minutes')
button_hours = InlineKeyboardButton(text = 'Час(а)', callback_data = 'hours')

time_formar = InlineKeyboardMarkup()
time_formar.add(button_minutes)
time_formar.add(button_hours)



def add_new_user(user_id, user_name):
	YES = InlineKeyboardButton(text = u'Дать доступ', callback_data = 'add_approve %s %s' % (user_id, user_name))
	NO = InlineKeyboardButton(text = u'Запретить', callback_data = 'add_decline %s' % (user_id))
	access = InlineKeyboardMarkup()
	access.add(YES)
	access.add(NO)
	return access

def add_ssh(user_id, user_name):
	ssh_button_yes = InlineKeyboardButton(text = u'Добавить', callback_data = 'ssh_approve %s %s' % (user_id, user_name))
	ssh_button_no = InlineKeyboardButton(text = u'Не добавлять', callback_data = 'ssh_decline %s %s' % (user_id, user_name))
	ssh = InlineKeyboardMarkup()
	ssh.add(ssh_button_yes)
	ssh.add(ssh_button_no)
	return ssh

def generate_buttons(users):
	del_buttons = InlineKeyboardMarkup()
	# for i in users:
	# 	print(i.firstname, i.user_id)
	for item in users:
		del_buttons.add(InlineKeyboardButton(text = '%s (id:%s)' % (item.firstname, item.user_id ), callback_data = '%s %s %s' % ("del", item.user_id, item.firstname)))
	return del_buttons