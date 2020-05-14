from django.db import models

class Profile(models.Model):
    name = models.CharField(max_length = 30)
    red = models.IntegerField(default=0)
    green = models.IntegerField(default=0)
    blue = models.IntegerField(default=0)
    speed = models.IntegerField()
    brightness = models.IntegerField()
    timeout = models.IntegerField()

    def __str__(self):
        return self.name

class UserProfile(models.Model):
    current_profile = models.OneToOneField(Profile, on_delete=models.CASCADE)

    def save(self, *args, **kwargs):
        if not self.pk and UserProfile.objects.exists():
            raise BaseException('There can be only one UserProfile instance')
        return super(UserProfile, self).save(*args, **kwargs)

    def __str__(self):
        return self.current_profile.name


