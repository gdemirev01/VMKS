from rest_framework import generics
from rest_framework.views import APIView
from django.contrib.auth.models import User

from .models import Profile, UserProfile
from .serializers import ProfileSerializer, UserProfileSerializer, UserProfileSerializerGet

class ProfileList(generics.ListCreateAPIView):
    queryset = Profile.objects.all()
    serializer_class = ProfileSerializer

class ProfileDetail(generics.RetrieveUpdateDestroyAPIView):
    queryset = Profile.objects.all()
    serializer_class = ProfileSerializer

class UserProfileUpdate(generics.UpdateAPIView):
    serializer_class = UserProfileSerializer

    def get_object(self):
        current_profile = UserProfile.objects.all()[0]
        return current_profile

class UserProfileDetail(generics.RetrieveAPIView):
    serializer_class = UserProfileSerializerGet

    def get_object(self):
        current_profile = UserProfile.objects.all()[0]
        return current_profile