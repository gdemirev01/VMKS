# Generated by Django 3.0 on 2020-04-09 14:55

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('ledSettings', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='profile',
            name='brightness',
            field=models.CharField(default=django.utils.timezone.now, max_length=30),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='profile',
            name='color',
            field=models.CharField(default=django.utils.timezone.now, max_length=30),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='profile',
            name='speed',
            field=models.CharField(default=django.utils.timezone.now, max_length=70),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='profile',
            name='turn_off_time',
            field=models.TimeField(default=django.utils.timezone.now),
            preserve_default=False,
        ),
    ]