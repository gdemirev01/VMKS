from rest_framework import serializers
from django.contrib.auth.models import User

from .models import Profile, UserProfile

class ProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = Profile
        fields = ('id', 'name', 'color', 'speed', 'brightness', 'timeout',)
        depth = 1

class UserProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = UserProfile
        fields = ("current_profile",)

class UserProfileSerializerGet(serializers.ModelSerializer):
    class Meta:
        model = UserProfile
        fields = ("current_profile",)
        depth = 1
