# Generated by Django 3.0 on 2020-04-09 19:05

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('ledSettings', '0006_userprofile'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='userprofile',
            name='user',
        ),
    ]
