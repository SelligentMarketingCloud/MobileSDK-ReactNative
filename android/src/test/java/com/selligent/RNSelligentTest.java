package com.selligent;


import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Resources;
import android.graphics.Color;
import android.util.Log;

import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;
import com.selligent.sdk.SMEvent;
import com.selligent.sdk.SMEventUserLogin;
import com.selligent.sdk.SMForegroundGcmBroadcastReceiver;
import com.selligent.sdk.SMInAppMessage;
import com.selligent.sdk.SMInAppMessageReturn;
import com.selligent.sdk.SMInAppRefreshType;
import com.selligent.sdk.SMManager;
import com.selligent.sdk.SMMessageType;
import com.selligent.sdk.SMNotificationButton;
import com.selligent.sdk.SMNotificationMessage;
import com.selligent.sdk.SMObserverManager;
import com.selligent.sdk.SMRemoteMessageDisplayType;
import com.selligent.sdk.SMSettings;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.mockito.MockedConstruction;
import org.mockito.MockedStatic;
import org.mockito.Mockito;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;

import java.util.ArrayList;
import java.util.HashMap;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.LifecycleOwner;
import androidx.lifecycle.Observer;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

@SuppressWarnings({"ResultOfMethodCallIgnored", "unchecked"})
public class RNSelligentTest
{
    private SMManager smManager;
    private ReactApplicationContext reactApplicationContext;
    private RNSelligent spiedRNSelligent;
    private RNSelligent rnSelligent;
    private LocalBroadcastManager localBroadcastManager;
    private MockedStatic<RNSelligent> mockedStaticRNSelligent;
    private MockedStatic<Log> mockedStaticLog;
    private MockedStatic<Color> mockedStaticColor;
    private MockedStatic<LocalBroadcastManager> mockedStaticLocalBroadcastManager;

    @Before
    public void setUp()
    {
        smManager = Mockito.mock(SMManager.class);
        reactApplicationContext = Mockito.mock(ReactApplicationContext.class);
        localBroadcastManager = Mockito.mock(LocalBroadcastManager.class);
        mockedStaticLog = Mockito.mockStatic(Log.class);
        mockedStaticColor = Mockito.mockStatic(Color.class);
        mockedStaticLocalBroadcastManager = Mockito.mockStatic(LocalBroadcastManager.class);

        mockedStaticRNSelligent = Mockito.mockStatic(RNSelligent.class);
        mockedStaticRNSelligent.when(RNSelligent::getSMManager).thenReturn(smManager);

        mockedStaticLocalBroadcastManager.when(() -> LocalBroadcastManager.getInstance(Mockito.any(Context.class))).thenReturn(localBroadcastManager);

        rnSelligent = new RNSelligent(reactApplicationContext);
        spiedRNSelligent = Mockito.spy(rnSelligent);
    }

    @After
    public void tearDown()
    {
        mockedStaticRNSelligent.close();
        mockedStaticLog.close();
        mockedStaticColor.close();
        mockedStaticLocalBroadcastManager.close();
        SMManager.NOTIFICATION_ACTIVITY = null;
    }

    @Test
    public void init()
    {
        //GIVEN
        //WHEN
        //THEN
        Mockito.verify(reactApplicationContext).addActivityEventListener(rnSelligent);
        Mockito.verify(reactApplicationContext).addLifecycleEventListener(rnSelligent);
    }

    @Test
    public void getName()
    {
        //GIVEN
        //WHEN
        String name = spiedRNSelligent.getName();

        //THEN
        Assert.assertEquals("RNSelligent", name);
    }

    @Test
    public void configure()
    {
        //GIVEN
        Resources resources = Mockito.mock(Resources.class);
        Application app = Mockito.mock(Application.class);
        int resourceId = 10;

        mockedStaticRNSelligent.when(() -> RNSelligent.configure(Mockito.any(Application.class))).thenCallRealMethod();
        mockedStaticRNSelligent.when(RNSelligent::getSelligentSettings).thenReturn("{\"url\": \"SomeUrl\",\n" +
                        "    \"clientId\": \"someClientId\",\n" +
                        "    \"privateKey\": \"somePrivateKey\",\n" +
                        "    \"delayedPushAction\": true,\n" +
                        "    \"interceptSelligentUniversalLinks\": true,\n" +
                        "    \"fullyQualifiedNotificationActivityClassName\": \"com.mycompany.myapp.MainActivity\",\n" +
                        "    \"inAppMessageRefreshType\": 11,\n" +
                        "    \"notificationSmallIcon\": \"someIcon\",\n" +
                        "    \"notificationIconColor\": \"#ffffff\",\n" +
                        "    \"addInAppMessageFromPushToInAppMessageList\": true}");
        mockedStaticRNSelligent.when(() -> RNSelligent.getActivityClass(Mockito.anyString())).thenReturn(SomeActivity.class);
        mockedStaticColor.when(() -> Color.parseColor(Mockito.anyString())).thenReturn(resourceId);

        Mockito.doReturn(resources).when(app).getResources();
        Mockito.doReturn("somePackageName").when(app).getPackageName();
        Mockito.doReturn(resourceId).when(resources).getIdentifier(Mockito.anyString(), Mockito.anyString(), Mockito.anyString());

        //WHEN
        RNSelligent.configure(app);

        //THEN
        Mockito.verify(smManager).start(Mockito.any(SMSettings.class), Mockito.eq(app));
        Mockito.verify(smManager).setNotificationSmallIcon(resourceId);
        Mockito.verify(smManager).setNotificationIconColor(resourceId);
        Assert.assertEquals(SomeActivity.class, SMManager.NOTIFICATION_ACTIVITY);
    }

    @Test
    public void getVersionLib()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        //WHEN
        spiedRNSelligent.getVersionLib(callback);

        //THEN
        Mockito.verify(callback).invoke(SMManager.VERSION_LIB);
    }

    @Test
    public void enableInAppMessages_boolean_true()
    {
        //GIVEN
        ReadableMap readableMap = Mockito.mock(ReadableMap.class);

        Mockito.doReturn(ReadableType.Boolean).when(readableMap).getType("enabled");
        Mockito.doReturn(true).when(readableMap).getBoolean("enabled");

        //WHEN
        spiedRNSelligent.enableInAppMessages(readableMap);

        //THEN
        Mockito.verify(smManager).enableInAppMessages(Mockito.any(SMInAppRefreshType.class));
    }

    @Test
    public void enableInAppMessages_boolean_false()
    {
        //GIVEN
        ReadableMap readableMap = Mockito.mock(ReadableMap.class);

        Mockito.doReturn(ReadableType.Boolean).when(readableMap).getType("enabled");
        Mockito.doReturn(false).when(readableMap).getBoolean("enabled");

        //WHEN
        spiedRNSelligent.enableInAppMessages(readableMap);

        //THEN
        Mockito.verify(smManager).disableInAppMessages();
    }

    @Test
    public void enableInAppMessages_int_None()
    {
        //GIVEN
        ReadableMap readableMap = Mockito.mock(ReadableMap.class);

        Mockito.doReturn(ReadableType.Number).when(readableMap).getType("enabled");
        Mockito.doReturn(10).when(readableMap).getInt("enabled");

        //WHEN
        spiedRNSelligent.enableInAppMessages(readableMap);

        //THEN
        Mockito.verify(smManager).enableInAppMessages(SMInAppRefreshType.None);
    }

    @Test
    public void enableInAppMessages_int_Minutely()
    {
        //GIVEN
        ReadableMap readableMap = Mockito.mock(ReadableMap.class);

        Mockito.doReturn(ReadableType.Number).when(readableMap).getType("enabled");
        Mockito.doReturn(11).when(readableMap).getInt("enabled");

        //WHEN
        spiedRNSelligent.enableInAppMessages(readableMap);

        //THEN
        Mockito.verify(smManager).enableInAppMessages(SMInAppRefreshType.Minutely);
    }

    @Test
    public void enableInAppMessages_int_Hourly()
    {
        //GIVEN
        ReadableMap readableMap = Mockito.mock(ReadableMap.class);

        Mockito.doReturn(ReadableType.Number).when(readableMap).getType("enabled");
        Mockito.doReturn(12).when(readableMap).getInt("enabled");

        //WHEN
        spiedRNSelligent.enableInAppMessages(readableMap);

        //THEN
        Mockito.verify(smManager).enableInAppMessages(SMInAppRefreshType.Hourly);
    }

    @Test
    public void enableInAppMessages_int_Daily()
    {
        //GIVEN
        ReadableMap readableMap = Mockito.mock(ReadableMap.class);

        Mockito.doReturn(ReadableType.Number).when(readableMap).getType("enabled");
        Mockito.doReturn(13).when(readableMap).getInt("enabled");

        //WHEN
        spiedRNSelligent.enableInAppMessages(readableMap);

        //THEN
        Mockito.verify(smManager).enableInAppMessages(SMInAppRefreshType.Daily);
    }

    @Test
    public void areInAppMessagesEnabled_true()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        Mockito.doReturn(true).when(smManager).areInAppMessagesEnabled();

        //WHEN
        spiedRNSelligent.areInAppMessagesEnabled(callback);

        //THEN
        Mockito.verify(callback).invoke(true);
    }

    @Test
    public void areInAppMessagesEnabled_false()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        Mockito.doReturn(false).when(smManager).areInAppMessagesEnabled();

        //WHEN
        spiedRNSelligent.areInAppMessagesEnabled(callback);

        //THEN
        Mockito.verify(callback).invoke(false);
    }

    @Test
    public void displayMessage()
    {
        //GIVEN
        String messageId = "someMessageId";
        Activity currentActivity = Mockito.mock(Activity.class);

        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();

        //WHEN
        spiedRNSelligent.displayMessage(messageId);

        //THEN
        Mockito.verify(smManager).displayInAppMessage(messageId, currentActivity);
    }

    /* Skipped because WritableNativeMap cannot be instantiateed or mocked in a unit test context...
    @Test
    public void getInAppMessages()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.getInAppMessages(callback);

        //THEN
        Mockito.verify(callback).invoke();
    }
*/

    @Test
    public void setInAppMessageAsSeen_success()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.setInAppMessageAsSeen("id3", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager).setInAppMessageAsSeen(inAppMessages.get(2));
        Mockito.verify(successCallback).invoke();
    }

    @Test
    public void setInAppMessageAsSeen_error()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.setInAppMessageAsSeen("id4", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager, Mockito.never()).setInAppMessageAsSeen(Mockito.any(SMInAppMessage.class));
        Mockito.verify(errorCallback).invoke("No message with id id4 found");
    }

    @Test
    public void setInAppMessageAsUnseen_success()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.setInAppMessageAsUnseen("id3", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager).setInAppMessageAsUnseen(inAppMessages.get(2));
        Mockito.verify(successCallback).invoke();
    }

    @Test
    public void setInAppMessageAsUnseen_error()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.setInAppMessageAsUnseen("id4", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager, Mockito.never()).setInAppMessageAsUnseen(Mockito.any(SMInAppMessage.class));
        Mockito.verify(errorCallback).invoke("No message with id id4 found");

    }

    @Test
    public void setInAppMessageAsDeleted_success()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.setInAppMessageAsDeleted("id3", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager).deleteInAppMessage("id3");
        Mockito.verify(successCallback).invoke();
    }

    @Test
    public void setInAppMessageAsDeleted_error()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.setInAppMessageAsDeleted("id4", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager, Mockito.never()).deleteInAppMessage("id4");
        Mockito.verify(errorCallback).invoke("No message with id id4 found");

    }

    @Test
    public void executeButtonAction_success()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html, "btId1", "buttonLabel1"));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image, "btId2", "buttonLabel3"));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.executeButtonAction("btId1", "id2", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager).executeButtonAction(reactApplicationContext, inAppMessages.get(1).getButtons()[0], inAppMessages.get(1));
        Mockito.verify(successCallback).invoke();
    }

    @Test
    public void executeButtonAction_error_no_inapp()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html, "btId1", "buttonLabel1"));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image, "btId2", "buttonLabel3"));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.executeButtonAction("btId1", "id4", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager, Mockito.never()).executeButtonAction(Mockito.any(Context.class), Mockito.any(SMNotificationButton.class),
                Mockito.any(SMInAppMessage.class));
        Mockito.verify(errorCallback).invoke("No message with id id4 found");
    }

    @Test
    public void executeButtonAction_error_no_button()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ArrayList<SMInAppMessage> inAppMessages = new ArrayList<>();

        inAppMessages.add(getMockedInAppMessage("id1", "title1", "body1", 11111, 11122,11112,
                true, SMMessageType.Alert));
        inAppMessages.add(getMockedInAppMessage("id2", "title2", "body2", 22222, 22233,22223,
                false, SMMessageType.Html, "btId1", "buttonLabel1"));
        inAppMessages.add(getMockedInAppMessage("id3", "title3", "body3", 33333, 33344,33334,
                false, SMMessageType.Image, "btId2", "buttonLabel3"));

        Mockito.doAnswer(invocation -> {
            ((SMInAppMessageReturn)invocation.getArgument(0)).onRetrieve(inAppMessages);
            return null;
        }).when(smManager).getInAppMessages(Mockito.any(SMInAppMessageReturn.class));

        //WHEN
        spiedRNSelligent.executeButtonAction("btId1", "id1", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager, Mockito.never()).executeButtonAction(Mockito.any(Context.class), Mockito.any(SMNotificationButton.class),
                Mockito.any(SMInAppMessage.class));
        Mockito.verify(errorCallback).invoke("buttonId does not exist in message.");
    }

    @Test
    public void setDebug()
    {
        //GIVEN

        //WHEN
        spiedRNSelligent.setDebug(true);

        //THEN
        Assert.assertTrue(SMManager.DEBUG);
    }

    @Test
    public void sendEvent_success()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ReadableMap event = Mockito.mock(ReadableMap.class);
        HashMap<String, Object> hashMap = new HashMap<>();

        hashMap.put("type", 92D);
        hashMap.put("email", "someEmail");

        Mockito.doReturn(hashMap).when(event).toHashMap();
        Mockito.doAnswer(invocation -> {
            ((SMEvent)invocation.getArgument(0)).Callback.onSuccess("ok");
            return null;
        }).when(smManager).sendSMEvent(Mockito.any(SMEvent.class));

        //WHEN
        spiedRNSelligent.sendEvent(event, successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager).sendSMEvent(Mockito.argThat(smEvent ->
                smEvent instanceof SMEventUserLogin && ((SMEventUserLogin)smEvent).Profile.equals("someEmail")));
        Mockito.verify(successCallback).invoke("ok");
    }

    @Test
    public void sendEvent_error()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);
        ReadableMap event = Mockito.mock(ReadableMap.class);
        HashMap<String, Object> hashMap = new HashMap<>();

        hashMap.put("type", 92D);
        hashMap.put("email", "someEmail");

        Mockito.doReturn(hashMap).when(event).toHashMap();
        Mockito.doAnswer(invocation -> {
            ((SMEvent)invocation.getArgument(0)).Callback.onError(404, new Exception("BOOM!"));
            return null;
        }).when(smManager).sendSMEvent(Mockito.any(SMEvent.class));

        //WHEN
        spiedRNSelligent.sendEvent(event, successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager).sendSMEvent(Mockito.argThat(smEvent ->
                smEvent instanceof SMEventUserLogin && ((SMEventUserLogin)smEvent).Profile.equals("someEmail")));
        Mockito.verify(errorCallback).invoke(404);
    }

    @Test
    public void getDeviceId()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);
        String deviceId = "someDeviceId";

        Mockito.doReturn(deviceId).when(smManager).getDeviceId();

        //WHEN
        spiedRNSelligent.getDeviceId(callback);

        //THEN
        Mockito.verify(callback).invoke(deviceId);
    }

    @Test
    public void enableNotifications_true()
    {
        //GIVEN

        //WHEN
        spiedRNSelligent.enableNotifications(true);

        //THEN
        Mockito.verify(smManager).enableNotifications();
    }

    @Test
    public void enableNotifications_false()
    {
        //GIVEN

        //WHEN
        spiedRNSelligent.enableNotifications(false);

        //THEN
        Mockito.verify(smManager).disableNotifications();
    }

    @Test
    public void displayLastReceivedRemotePushNotification()
    {
        //GIVEN
        Activity currentActivity = Mockito.mock(Activity.class);

        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();

        //WHEN
        spiedRNSelligent.displayLastReceivedRemotePushNotification("");

        //THEN
        Mockito.verify(smManager).displayLastReceivedNotificationContent(currentActivity);
    }

    @Test
    public void displayLastReceivedNotification()
    {
        //GIVEN

        //WHEN
        spiedRNSelligent.displayLastReceivedNotification();

        //THEN
        Mockito.verify(smManager).displayLastReceivedNotification();
    }

    /* Skipped because WritableNativeMap cannot be instantiateed or mocked in a unit test context...
    @Test
    public void getLastRemotePushNotification()
    {
        //GIVEN

        //WHEN

        //THEN
    }
    */


    @Test
    public void setNotificationSmallIcon()
    {
        //GIVEN
        Resources resources = Mockito.mock(Resources.class);
        int resourceId = 10;

        Mockito.doReturn(resources).when(reactApplicationContext).getResources();
        Mockito.doReturn("somePackageName").when(reactApplicationContext).getPackageName();
        Mockito.doReturn(resourceId).when(resources).getIdentifier(Mockito.anyString(), Mockito.anyString(), Mockito.anyString());

        //WHEN
        spiedRNSelligent.setNotificationSmallIcon("someIcon");

        //THEN
        Mockito.verify(smManager).setNotificationSmallIcon(resourceId);
    }

    @Test
    public void setNotificationLargeIcon()
    {
        //GIVEN
        Resources resources = Mockito.mock(Resources.class);
        int resourceId = 10;

        Mockito.doReturn(resources).when(reactApplicationContext).getResources();
        Mockito.doReturn("somePackageName").when(reactApplicationContext).getPackageName();
        Mockito.doReturn(resourceId).when(resources).getIdentifier(Mockito.anyString(), Mockito.anyString(), Mockito.anyString());

        //WHEN
        spiedRNSelligent.setNotificationLargeIcon("someIcon");

        //THEN
        Mockito.verify(smManager).setNotificationLargeIcon(resourceId);
    }

    @Test
    public void setNotificationIconColor_success()
    {
        //GIVEN
        int color = 10;
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);

        mockedStaticColor.when(() -> Color.parseColor(Mockito.anyString())).thenReturn(color);

        //WHEN
        spiedRNSelligent.setNotificationIconColor("someColor", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager).setNotificationIconColor(color);
        Mockito.verify(successCallback).invoke();
    }

    @Test
    public void setNotificationIconColor_error()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);

        mockedStaticColor.when(() -> Color.parseColor(Mockito.anyString())).thenThrow(new IllegalArgumentException("BOOM!"));

        //WHEN
        spiedRNSelligent.setNotificationIconColor("someColor", successCallback, errorCallback);

        //THEN
        Mockito.verify(smManager, Mockito.never()).setNotificationIconColor(Mockito.anyInt());
        Mockito.verify(errorCallback).invoke("color must be a color hex string.");
    }

    @Test
    public void setNotificationActivity_success()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);

        //WHEN
        spiedRNSelligent.setNotificationActivity("com.selligent.SomeActivity", successCallback, errorCallback);

        //THEN
        Assert.assertEquals(SomeActivity.class, SMManager.NOTIFICATION_ACTIVITY);
        Mockito.verify(successCallback).invoke();
    }

    @Test
    public void setNotificationActivity_error()
    {
        //GIVEN
        Callback successCallback = Mockito.mock(Callback.class);
        Callback errorCallback = Mockito.mock(Callback.class);

        //WHEN
        spiedRNSelligent.setNotificationActivity("SomeOtherActivity", successCallback, errorCallback);

        //THEN
        Assert.assertNull(SMManager.NOTIFICATION_ACTIVITY);
        Mockito.verify(errorCallback).invoke("Activity SomeOtherActivity not found.");
    }

    @Test
    public void getGCMToken()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);
        String token = "someToken";

        Mockito.doReturn(token).when(smManager).getGCMToken();

        //WHEN
        spiedRNSelligent.getGCMToken(callback);

        //THEN
        Mockito.verify(callback).invoke(token);
    }

    @Test
    public void getRemoteMessagesDisplayType_Automatic()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        Mockito.doReturn(SMRemoteMessageDisplayType.Automatic).when(smManager).getRemoteMessagesDisplayType();

        //WHEN
        spiedRNSelligent.getRemoteMessagesDisplayType(callback);

        //THEN
        Mockito.verify(callback).invoke(20);
    }

    @Test
    public void getRemoteMessagesDisplayType_None()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        Mockito.doReturn(SMRemoteMessageDisplayType.None).when(smManager).getRemoteMessagesDisplayType();

        //WHEN
        spiedRNSelligent.getRemoteMessagesDisplayType(callback);

        //THEN
        Mockito.verify(callback).invoke(21);
    }

    @Test
    public void getRemoteMessagesDisplayType_Notification()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        Mockito.doReturn(SMRemoteMessageDisplayType.Notification).when(smManager).getRemoteMessagesDisplayType();

        //WHEN
        spiedRNSelligent.getRemoteMessagesDisplayType(callback);

        //THEN
        Mockito.verify(callback).invoke(22);
    }

    @Test
    public void areNotificationsEnabled_true()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        Mockito.doReturn(true).when(smManager).areNotificationEnabled();

        //WHEN
        spiedRNSelligent.areNotificationsEnabled(callback);

        //THEN
        Mockito.verify(callback).invoke(true);
    }

    @Test
    public void areNotificationsEnabled_false()
    {
        //GIVEN
        Callback callback = Mockito.mock(Callback.class);

        Mockito.doReturn(false).when(smManager).areNotificationEnabled();

        //WHEN
        spiedRNSelligent.areNotificationsEnabled(callback);

        //THEN
        Mockito.verify(callback).invoke(false);
    }

    @Test
    public void subscribeToEvents_No_Activity()
    {
        //GIVEN
        SMObserverManager observerManager = Mockito.mock(SMObserverManager.class);

        Mockito.doReturn(null).when(reactApplicationContext).getCurrentActivity();

        //WHEN
        spiedRNSelligent.subscribeToEvents(null);

        //THEN
        Mockito.verifyNoInteractions(observerManager);
        Mockito.verifyNoInteractions(localBroadcastManager);
    }

    @Test
    public void subscribeToEvents_Activity_not_appCompatActivity()
    {
        //GIVEN
        Activity currentActivity = Mockito.mock(Activity.class);
        SMObserverManager observerManager = Mockito.mock(SMObserverManager.class);
        ReadableArray customEvents = Mockito.mock(ReadableArray.class);
        String customEvent = "someEvent";

        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();
        Mockito.doReturn(1).when(customEvents).size();
        Mockito.doReturn(customEvent).when(customEvents).getString(0);

        try(MockedConstruction<EventReceiver> mockedReceiver = Mockito.mockConstruction(EventReceiver.class))
        {
            try(MockedConstruction<IntentFilter> mockedintentFilter = Mockito.mockConstruction(IntentFilter.class))
            {
                //WHEN
                spiedRNSelligent.subscribeToEvents(customEvents);

                //THEN
                Mockito.verifyNoInteractions(observerManager);
                Mockito.verify(localBroadcastManager).registerReceiver(mockedReceiver.constructed().get(0),
                        mockedintentFilter.constructed().get(0));
                Mockito.verify(mockedintentFilter.constructed().get(0), Mockito.times(6)).addAction(Mockito.anyString());
            }
        }
    }

    @Test
    public void subscribeToEvents_Activity_is_appCompatActivity()
    {
        //GIVEN
        AppCompatActivity currentActivity = Mockito.mock(AppCompatActivity.class);
        SMObserverManager observerManager = Mockito.mock(SMObserverManager.class);
        ReadableArray customEvents = Mockito.mock(ReadableArray.class);

        spiedRNSelligent.areObserverStarted = false;

        Mockito.doReturn(observerManager).when(smManager).getObserverManager();
        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();
        Mockito.doAnswer(invocation -> {
            ((Runnable)invocation.getArgument(0)).run();
            return null;
        }).when(currentActivity).runOnUiThread(Mockito.any(Runnable.class));

        //WHEN
        spiedRNSelligent.subscribeToEvents(customEvents);

        //THEN
        Mockito.verify(observerManager).observeClickedButton(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verify(observerManager).observeDeviceId(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verify(observerManager).observeToken(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verify(observerManager).observeDismissedMessage(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verify(observerManager).observeDisplayedMessage(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verify(observerManager).observeEvent(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verify(observerManager).observePushReceived(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verify(observerManager).observeInAppMessages(Mockito.eq(currentActivity), Mockito.any(Observer.class));
        Mockito.verifyNoInteractions(localBroadcastManager);
    }

    @Test
    public void subscribeToEvents_observers_already_initialized()
    {
        //GIVEN
        AppCompatActivity currentActivity = Mockito.mock(AppCompatActivity.class);
        SMObserverManager observerManager = Mockito.mock(SMObserverManager.class);
        ReadableArray customEvents = Mockito.mock(ReadableArray.class);

        spiedRNSelligent.areObserverStarted = true;

        Mockito.doReturn(observerManager).when(smManager).getObserverManager();
        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();

        //WHEN
        spiedRNSelligent.subscribeToEvents(customEvents);

        //THEN
        Mockito.verifyNoInteractions(observerManager);
        Mockito.verifyNoInteractions(localBroadcastManager);
    }

    /* Skipped because WritableNativeMap cannot be instantiateed or mocked in a unit test context...
    @Test
    public void getBroadcastData()
    {
        //GIVEN

        //WHEN

        //THEN
    }*/

    @Test
    public void setFirebaseToken()
    {
        //GIVEN
        String token = "someToken";

        //WHEN
        spiedRNSelligent.setFirebaseToken(token);

        //THEN
        Mockito.verify(smManager).setFirebaseToken(token);
    }

    @Test
    public void onHostResume_receiver_doesnt_exist()
    {
        //GIVEN
        Activity currentActivity = Mockito.mock(Activity.class);
        Intent intent = Mockito.mock(Intent.class);

        spiedRNSelligent.receiver = null;

        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();
        Mockito.doReturn(intent).when(currentActivity).getIntent();

        //WHEN
        try (MockedConstruction<SMForegroundGcmBroadcastReceiver> mockedReceiver = Mockito.mockConstruction(SMForegroundGcmBroadcastReceiver.class))
        {
            spiedRNSelligent.onHostResume();

            //THEN
            Assert.assertEquals(mockedReceiver.constructed().get(0), spiedRNSelligent.receiver);
            Mockito.verify(mockedReceiver.constructed().get(0)).getIntentFilter();
            Mockito.verify(currentActivity).registerReceiver(mockedReceiver.constructed().get(0), null);
            Mockito.verify(smManager).checkAndDisplayMessage(intent, currentActivity);
        }
    }

    @Test
    public void onHostResume_receiver_already_exists()
    {
        //GIVEN
        Activity currentActivity = Mockito.mock(Activity.class);
        Intent intent = Mockito.mock(Intent.class);

        spiedRNSelligent.receiver = Mockito.mock(SMForegroundGcmBroadcastReceiver.class);

        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();
        Mockito.doReturn(intent).when(currentActivity).getIntent();

        //WHEN
        spiedRNSelligent.onHostResume();

        //THEN
        Mockito.verify(currentActivity).registerReceiver(Mockito.eq(spiedRNSelligent.receiver), Mockito.any());
        Mockito.verify(smManager).checkAndDisplayMessage(intent, currentActivity);
    }

    @Test
    public void onHostPause()
    {
        //GIVEN
        Activity currentActivity = Mockito.mock(Activity.class);

        spiedRNSelligent.receiver = Mockito.mock(SMForegroundGcmBroadcastReceiver.class);

        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();

        //WHEN
        spiedRNSelligent.onHostPause();

        //THEN
        Mockito.verify(currentActivity).unregisterReceiver(spiedRNSelligent.receiver);
    }

    @Test
    public void onNewIntent()
    {
        //GIVEN
        Activity currentActivity = Mockito.mock(Activity.class);
        Intent intent = Mockito.mock(Intent.class);

        Mockito.doReturn(currentActivity).when(reactApplicationContext).getCurrentActivity();

        //WHEN
        spiedRNSelligent.onNewIntent(intent);

        //THEN
        Mockito.verify(smManager).checkAndDisplayMessage(intent, currentActivity);
    }

    private SMInAppMessage getMockedInAppMessage(String id, String title, String body, long creationDate, long expirationDate, long receptionDate,
                                                 boolean hasBeenSeen, SMMessageType type)
    {
        return getMockedInAppMessage(id, title, body, creationDate, expirationDate, receptionDate, hasBeenSeen, type, null, null);
    }

    private SMInAppMessage getMockedInAppMessage(String id, String title, String body, long creationDate, long expirationDate, long receptionDate,
                                                 boolean hasBeenSeen, SMMessageType type, String buttonId, String buttonLabel)
    {
        SMInAppMessage inAppMessage = Mockito.mock(SMInAppMessage.class);

        inAppMessage.id = id;
        inAppMessage.title = title;
        Mockito.doReturn(body).when(inAppMessage).getBody();
        Mockito.doReturn(creationDate).when(inAppMessage).getCreationDate();
        Mockito.doReturn(expirationDate).when(inAppMessage).getExpirationDate();
        Mockito.doReturn(receptionDate).when(inAppMessage).getReceptionDate();
        Mockito.doReturn(hasBeenSeen).when(inAppMessage).hasBeenSeen();
        Mockito.doReturn(type).when(inAppMessage).getType();

        if ((buttonId != null) && (buttonLabel != null))
        {
            SMNotificationButton button = Mockito.mock(SMNotificationButton.class);

            button.id = buttonId;
            button.label = buttonLabel;
            Mockito.doReturn(new SMNotificationButton[]{button}).when(inAppMessage).getButtons();
        }

        return inAppMessage;
    }
}

class SomeActivity extends Activity
{
}